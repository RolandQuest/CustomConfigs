#include "cc/ccportal.h"

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>

#include "cc/cc_component_configuration.h"
#include "cc/cc_component.h"
#include "cc/cc_loader.h"
#include "cc/cc_factory.h"
#include "acc/cclog.h"

namespace cc
{
    
    //Member variables
    ConfigurationMap _ConfigMap;
    ComponentMap _CompMap;
    cc_loader* _Loader = nullptr;
    std::vector<cc_factory*> _FactoryVector;
    
    
    //Private functions.
    
    bool instantiate()
    {
        //TODO: isSuccess is not used... should be using it here.
        bool isSuccess = true;
        for(auto& item : _ConfigMap)
        {
            _CompMap[item.first] = (item.second)->Instantiate();
        }
        
        if(isSuccess)
        {
            Log("Instantiation successful!");
        }
        
        return isSuccess;
    }
    
    bool link()
    {
        bool isSuccess = true;
        for(auto& entry : _CompMap)
        {
            //TODO: Pass through as constant.
            bool localIsSuccess = (entry.second)->Link(_CompMap);
            isSuccess &= localIsSuccess;
            
            if(!localIsSuccess)
            {
                Log("Linking issue with component '", entry.first, "'.");
            }
        }
        
        if(isSuccess)
        {
            Log("Linking successful!");
        }
        
        return isSuccess;
    }
    
    bool validate()
    {
        bool isSuccess = true;
        for(auto& entry : _ConfigMap)
        {
            bool localIsSuccess = (entry.second)->Validate();
            isSuccess &= localIsSuccess;
            
            if(!localIsSuccess)
            {
                Log("Component '",entry.first,"' validation failed!");
            }
        }
        
        if(isSuccess)
        {
            Log("Validation successful!");
        }
        
        return isSuccess;
    }
    
    std::string ConstructPathString(const std::vector<std::string>& path)
    {
        std::string pathString = "";
        if(path.size() != 0)
        {
            pathString = path[0];
            for(size_t i = 1; i < path.size(); i++)
            {
                pathString += " -> " + path[i];
            }
        }
        return pathString;
    }
    
    bool PathContains(const std::vector<std::string>& path, const std::string& toSearch)
    {
        for(auto& entry : path)
        {
            if(entry == toSearch)
            {
                return true;
            }
        }
        return false;
    }
    
    void FindAllCirclesInvolving(const std::vector<std::string>& currentPath, const std::vector<std::string>& possibleNodes, ConfigurationMap& availableConfigurations, std::vector<std::string>& circles)
    {
        for(auto& entry : possibleNodes)
        {
            if(PathContains(currentPath, entry))
            {
                if(currentPath[0] == entry)
                {
                    circles.push_back(ConstructPathString(currentPath));
                }
                continue;
            }
            
            if(availableConfigurations.count(entry) == 0)
            {
                continue;
            }
            
            std::vector<std::string> nextPath(std::begin(currentPath),std::end(currentPath));
            nextPath.push_back(entry);
            
            std::vector<std::string> nextPossibleNodes = availableConfigurations[entry]->GetReferenceNames();
            
            FindAllCirclesInvolving(nextPath, nextPossibleNodes, availableConfigurations, circles);
        }
        
    }
    
    bool areCircularReferences(ConfigurationMap copyOfAvailableConfigurations)
    {
        std::vector<std::string> circles;
        
        while(copyOfAvailableConfigurations.size() > 0)
        {
            cc_component_configuration* startingNode = std::begin(copyOfAvailableConfigurations)->second;
            std::vector<std::string> currentPath;
            currentPath.push_back(startingNode->GetName());
            copyOfAvailableConfigurations.erase(std::begin(copyOfAvailableConfigurations));
            
            std::vector<std::string> possibleNodes = startingNode->GetReferenceNames();
            
            FindAllCirclesInvolving(currentPath, possibleNodes, copyOfAvailableConfigurations, circles);
        }
        
        bool isSuccess = !( (bool) circles.size() );
        
        if(isSuccess)
        {
            Log("Circular reference check successful.");
        }
        else
        {
            Log("Circular references found!");
            for(auto& circle : circles)
            {
                Log('\t', circle);
            }
        }
        
        return isSuccess;
    }
    
    
    
    //Public functions.
    
    void setCCLogFileBuf(std::filebuf* fileBuf)
    {
        _TargetFileBuffer = fileBuf;
    }
    
    void clearMap()
    {
        for(auto& entry : _ConfigMap)
        {
            delete entry.second;
        }
        _ConfigMap.clear();
        for(auto& entry : _CompMap)
        {
            delete entry.second;
        }
        _CompMap.clear();
        
        Log("Clear called on all maps.");
    }
    
    cc_loader* setLoader(cc_loader* loader)
    {
        _Loader = loader;
        Log("Loader set of type: ", typeid(&loader).name());
        return _Loader;
    }
    
    cc_factory* registerFactory(cc_factory* factory)
    {
        _FactoryVector.push_back(factory);
        Log("Factory registered of type: ", typeid(&factory).name());
        return factory;
    }
    
    bool GoodRegistry(const std::string& configFile)
    {
        bool isSuccess = true;
        if(_FactoryVector.size() == 0)
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
    
    bool load(const std::string& configFile)
    {
        if(!GoodRegistry(configFile))
        {
            return false;
        }

        bool isSuccess = true;
        isSuccess &= _Loader->Load(configFile, _ConfigMap, _FactoryVector);
        
        if(isSuccess)
        {
            Log("Loading successful!");
        }
        
        isSuccess &= validate();
        isSuccess &= instantiate();
        isSuccess &= link();
        isSuccess &= areCircularReferences(_ConfigMap);
        
        return isSuccess;
    }
}

