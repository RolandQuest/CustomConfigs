#include "cc/ccportal.h"

#include <vector>
#include <fstream>
#include <typeinfo>

#include "cc/cc_component.h"
#include "cc/cc_loader.h"
#include "cc/cc_factory.h"

namespace cc
{
    
    //Member variables
    cc_ComponentMap _CompMap;
    cc_loader* _Loader = nullptr;
    cc_FactorySet _FactorySet;
    int _UniqueNameIncrement = -1;

    //Private functions.
    bool loadAndLog(const std::string& fileName, std::set<std::string>* storage)
    {
        std::string errorMsg;
        cc_ComponentMap tempMap;
        
        if(!_Loader->cc_loader_load(fileName, tempMap, _FactorySet))
        {
            Log("Loading of file ", fileName, " failed.");
            return false;
        }
        
        for(auto& entry : tempMap)
        {
            if(_CompMap.count(entry.first) != 0)
            {
                Log("Component ", entry.first, " was already defined in the ComponentMap.");
                Log("Overriding the previous component in ComponentMap. Not deleting from memory.");
            }
            _CompMap[entry.first] = entry.second;
            
            if(storage != nullptr)
            {
                storage->insert(entry.first);
            }
        }
        
        Log("Loaded ", tempMap.size(), " new components into the map.");
        return true;
    }

    //Public functions.

    bool initialize()
    {
        bool isSuccess = true;
        for(auto& entry : _CompMap)
        {
            initialize(entry.second);
        }
        return isSuccess;
    }
    
    bool initialize(cc_component* compPointer)
    {
        static std::vector<cc_component*> _init_chain;

        if (compPointer->cc_is_initialized()) {
            return true;
        }

        _init_chain.push_back(compPointer);
        if (std::find(std::begin(_init_chain), std::end(_init_chain), compPointer) != (std::end(_init_chain) - 1))
        {
            Log("Failed to initialize ", compPointer->cc_component_name(), " component due to a chain initialize call.");

            std::string chainString = _init_chain[0]->cc_component_name();
            for (size_t i = 1; i < _init_chain.size(); i++)
            {
                chainString += " -> " + _init_chain[i]->cc_component_name();
            }
            Log("\t", chainString);
            return false;
        }

        bool localIsSuccess = compPointer->cc_initialize(_CompMap);

        if (!localIsSuccess)
        {
            Log("Failed to initialize ", compPointer->cc_component_name(), " component.");
        }

        _init_chain.clear();
        return localIsSuccess;
    }

    void setCCLogFileBuf(std::filebuf* fileBuf)
    {
        _cc_log_TargetFileBuffer = fileBuf;
    }
    
    void clearComponentMap()
    {
        for(auto& entry : _CompMap)
        {
            delete entry.second;
        }
        _CompMap.clear();
        
        Log("Clear called on component map.");
    }
    
    std::string getUniqueName()
    {
        _UniqueNameIncrement++;
        return _UniqueNameHeader + std::to_string(_UniqueNameIncrement);
    }

    bool checkForComponent(const std::string name)
    {
        return _CompMap.count(name) == 1;
    }
    
    cc_loader* setLoader(cc_loader* loader)
    {
        _Loader = loader;
        Log("Loader set of type: ", typeid(&loader).name());
        return _Loader;
    }
    
    cc_factory* registerFactory(cc_factory* factory)
    {
        _FactorySet.insert(factory);
        Log("Factory registered of type: ", typeid(&factory).name());
        return factory;
    }

    bool insertComponent(cc_component* component)
    {
        if (_CompMap.count(component->cc_component_name()) == 1) {
            return false;
        }
        _CompMap[component->cc_component_name()] = component;
        return true;
    }

    bool GoodRegistry(const std::string& configFile)
    {
        bool isSuccess = true;
        if(_FactorySet.size() == 0)
        {
            Log("No factories registered when loading ", configFile);
            isSuccess = false;
        }
        if(_Loader == nullptr)
        {
           Log("No loader set when loading ", configFile);
           isSuccess = false;
        }
        return isSuccess;
    }

    bool load(const std::string& configFile, std::set<std::string>* storage)
    {
        Log("");
        Log("Loading " + configFile + ".");
        Log("---------------------------");
        if (!GoodRegistry(configFile))
        {
            return false;
        }

        return loadAndLog(configFile, storage);
    }

    void serialize(std::ostream& stream) {

        for (auto& entry : _CompMap) {

            _Loader->cc_loader_serialize(stream, entry.second);
            stream.flush();
        }
    }
}

