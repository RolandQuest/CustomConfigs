#include "core/cc_core_loader.h"

#include <algorithm>
#include <sstream>

#include "cc/cc_component_configuration.h"
#include "cc/cc_factory.h"

namespace cc
{
    
    cc_core_loader::cc_core_loader()
    {
        //ctor
    }
    
    cc_core_loader::~cc_core_loader()
    {
        //dtor
    }
    
    bool cc_core_loader::Load(const std::string& configFile, ConfigurationMap& theMap, const std::vector<cc_factory*>& availableFactories)
    {
        _FileName = configFile;
        OpenFile();
        
        str_ConfigData configData;
        
        LineState
            currentState = BeginFile,
            previousState = BeginFile;
            
        while(NextLine())
        {
            SetState(currentState, previousState);
            switch(currentState)
            {
                case BeginFile:
                    break;
                    
                case NewConfiguration:
                    
                    if(previousState != BeginFile)
                    {
                        if(configData.IsValid())
                        {
                            FactoryWork(theMap, availableFactories, configData);
                        }
                    }
                    
                    ReadConfigurationLine(configData);
                    break;
                
                case ReadingConfiguration:
                    configData.Contents += _LineBeingRead + '\n';
                    break;
                    
            }
        }
        
        if(previousState !=  BeginFile)
        {
            FactoryWork(theMap, availableFactories, configData);
        }
        
        CloseFile();
        
        //TODO: No errors recorded yet.
        return true;
    }
    
    void cc_core_loader::SetState(LineState& currentState, LineState& previousState)
    {
        previousState = currentState;
        if(LineContainsConfigurationBanner())
        {
            currentState = NewConfiguration;
        }
        else if(currentState == NewConfiguration)
        {
            currentState = ReadingConfiguration;
        }
    }
    
    void cc_core_loader::FactoryWork(ConfigurationMap& myMap, const std::vector<cc_factory*>& availableFactories, const str_ConfigData& configData)
    {
        for(size_t i = 0; i < availableFactories.size(); i++)
        {
            if(availableFactories[i]->ContainsType(configData.Type))
            {
                cc_component_configuration* config = availableFactories[i]->CreateConfiguration(configData.Type, configData.Name, configData.Contents);
                myMap[configData.Name] = config;
                break;
            }
        }
    }
    
    bool cc_core_loader::LineContainsConfigurationBanner()
    {
        size_t pos = _LineBeingRead.find(_ConfigurationBanner);
        if(pos != std::string::npos)
        {
            return true;
        }
        return false;
    }
    
    void cc_core_loader::ReadConfigurationLine(str_ConfigData& configData)
    {
        configData.Clear();
        
        size_t pos = _LineBeingRead.find(_ConfigurationBanner);
        _LineBuffer.str(_LineBeingRead.substr(pos+_ConfigurationBanner.size(),std::string::npos));
        _LineBuffer.clear();
        
        _LineBuffer>>std::ws;
        _LineBuffer>>configData.Type;
        
        _LineBuffer>>std::ws;
        _LineBuffer>>configData.Name;
        
        //TODO: Log error if invalid str_ConfigData.
        
        if(!(_LineBuffer>>std::ws).eof())
        {
            _LineBuffer>>configData.Contents;
            configData.Contents += '\n';
        }
    }
    
}
