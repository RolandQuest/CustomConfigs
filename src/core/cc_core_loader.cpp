#include "core/cc_core_loader.h"

#include <sstream>

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
    
    bool cc_core_loader::Load(const std::string& configFile, ComponentMap& theMap, const std::set<cc_factory*>& availableFactories)
    {
        if(!LoadFile(configFile))
        {
            return false;
        }
        
        context_node* rootContext = new context_node();
        CreateContextTree(rootContext);
        CreateConfigurations(rootContext, theMap, availableFactories);
        return true;
    }
    
    std::vector<std::string> cc_core_loader::CreateConfigurations(context_node* parent, ComponentMap& theMap, const std::set<cc_factory*>& availableFactories)
    {
        for(auto& child : parent->_Children)
        {
            std::vector<std::string> childNames = CreateConfigurations(child.second, theMap, availableFactories);
            std::string expandedNames;
            
            for(auto& name : childNames)
            {
                expandedNames += " " + name + " ";
            }
            
            parent->ReplaceName(child.first, expandedNames);
        }
        
        std::vector<config_string> splitConfigs;
        SplitConfigs(parent->_NodeContents, splitConfigs);
        
        std::vector<std::string> allNames;
        for(const config_string& config : splitConfigs)
        {
            std::string name = CreateComponent(theMap, availableFactories, config);
            allNames.push_back(name);
        }
        
        return allNames;
    }
    
    void cc_core_loader::SplitConfigs(const config_string& config, std::vector<config_string>& container)
    {
        size_t
            endPos = 0,
            pos = config.Find(_ConfigurationBanner);
        
        while(pos != std::string::npos)
        {
            endPos = config.Find(_ConfigurationBanner, pos + 1);
            config_string localConfig = config.SubStr(pos + 1, endPos - pos - 1);
            container.push_back(localConfig);
            pos = config.Find(_ConfigurationBanner, pos + 1);;
        }
    }
    
    std::string cc_core_loader::CreateComponent(ComponentMap& theMap, const std::set<cc_factory*>& availableFactories, const config_string& config)
    {
        std::string
            type,
            name,
            contents;
            
        std::istringstream stream;
        stream.str(config.GetDataCopy());
        stream.clear();
        
        stream>>type>>name;
        
        while(!stream.eof())
        {
            contents += stream.get();
        }
        
        //TODO: Check valid comp first please.
        //Factory order no longer guaranteed.
        for(cc_factory* factory : availableFactories)
        {
            if(factory->ContainsType(type))
            {
                cc_component* comp = factory->CreateComponent(type, name, contents);
                theMap[name] = comp;
                break;
            }
        }
        
        return name;
    }
    
    void cc_core_loader::CreateContextTree(context_node* parent)
    {
        size_t lineNumber = parent->_ReferenceLineNumber;
        std::streampos pos = parent->_ReferencePos;
        
        int subContextCounter = 0;
        
        std::string fullLineContents;
        while(_FileContents.GetLineAt(fullLineContents, lineNumber, pos))
        {
            std::istringstream stream;
            stream.str(fullLineContents);
            stream.clear();
            
            std::string abreviatedLineContents;
            
            while(!stream.eof())
            {
                char nextChar = stream.get();
                
                switch(nextChar)
                {
                    case _ContextOpen:
                        
                        if(subContextCounter == 0)
                        {
                            std::string childName = GetUniqueName();
                            abreviatedLineContents += " " + childName + " ";
                            context_node* child = new context_node(parent, lineNumber, pos + stream.tellg());
                            CreateContextTree(child);
                            parent->_Children[childName] = child;
                        }
                        
                        subContextCounter++;
                        break;
                        
                    case _ContextClose:
                        
                        if(subContextCounter > 0)
                        {
                            subContextCounter--;
                        }
                        else
                        {
                            if(parent->IsRoot())
                            {
                                //What are you closing now?
                            }
                            else
                            {
                                parent->_NodeContents += abreviatedLineContents;
                                return;
                            }
                        }
                        
                        break;
                    
                    default:
                        
                        if(subContextCounter == 0)
                        {
                            abreviatedLineContents.push_back(nextChar);
                        }
                        break;
                }
            }
            
            parent->_NodeContents += abreviatedLineContents + '\n';
            pos = 0;
            lineNumber++;
        }
    }
    
    std::string cc_core_loader::GetUniqueName()
    {
        bool success = false;
        std::string testName;
        
        while(!success)
        {
            _UniqueNameIncrement++;
            testName = _UniqueNameHeader + std::to_string(_UniqueNameIncrement);
            success = _FileContents.Find(testName) == std::string::npos;
        }
        
        return testName;
    }
    
    
}
