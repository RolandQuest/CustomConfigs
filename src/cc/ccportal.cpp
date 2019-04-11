#include "cc/ccportal.h"

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <set>

#include "cc/cc_component.h"
#include "cc/cc_loader.h"
#include "cc/cc_factory.h"
#include "cc/cclog.h"

namespace cc
{
    
    //Member variables
    ComponentMap _CompMap;
    cc_loader* _Loader = nullptr;
    cc_configuration_mapper* _ConfigMapper = nullptr;
    std::set<cc_factory*> _FactorySet;
    
    
    //Private functions.
    
    bool loadAndLog(const std::string& fileName)
    {
        std::string errorMsg;
        ComponentMap tempMap;
        
        if(!_Loader->Load(fileName, tempMap, _FactorySet))
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
        }
        
        Log("Loaded ", tempMap.size(), " new components into the map.");
        return true;
    }
    
    bool initialize()
    {
        bool isSuccess = true;
        for(auto& entry : _CompMap)
        {
            bool localIsSuccess = (entry.second)->Initialize(_CompMap, _ConfigMapper);
            isSuccess &= localIsSuccess;
            
            if(!localIsSuccess)
            {
                Log("Failed to initialize ", entry.first, " component.");
            }
        }
        return isSuccess;
    }
    
    //Public functions.
    
    void setCCLogFileBuf(std::filebuf* fileBuf)
    {
        _TargetFileBuffer = fileBuf;
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
    
    cc_loader* setLoader(cc_loader* loader)
    {
        _Loader = loader;
        Log("Loader set of type: ", typeid(&loader).name());
        return _Loader;
    }
    
    cc_configuration_mapper* setConfigMapper(cc_configuration_mapper* mapper)
    {
        _ConfigMapper = mapper;
        Log("Mapper set of type: ", typeid(&mapper).name());
        return _ConfigMapper;
    }
    
    cc_factory* registerFactory(cc_factory* factory)
    {
        _FactorySet.insert(factory);
        Log("Factory registered of type: ", typeid(&factory).name());
        return factory;
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
        if(_ConfigMapper == nullptr)
        {
           Log("No configuration mapper set when loading ", configFile);
           isSuccess = false;
        }
        return isSuccess;
    }
    
    bool load(const std::string& configFile)
    {
        Log("");
        Log("Loading " + configFile + ".");
        Log("---------------------------");
        if(!GoodRegistry(configFile))
        {
            return false;
        }
        
        bool isSuccess = loadAndLog(configFile);
        isSuccess &= initialize();
        
        return isSuccess;
    }
}

