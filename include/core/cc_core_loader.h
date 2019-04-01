#ifndef CC_CORE_LOADER_H
#define CC_CORE_LOADER_H

#include <map>
#include <string>
#include <vector>

#include "cc/cc_loader.h"
#include "acc/cc_base_loader.h"
#include "core/context_node.h"

namespace cc
{
    
    class cc_component_configuration;
    class cc_factory;
    typedef std::map<std::string, cc_component_configuration*> ConfigurationMap;
    
    class cc_core_loader : public cc_loader, public cc_base_loader
    {
        public:
            
            cc_core_loader();
            virtual ~cc_core_loader();
            
            bool Load(const std::string& configFile, ConfigurationMap& theMap, const std::vector<cc_factory*>& availableFactories) override;
            
        private:
            
            std::vector<std::string> CreateConfigurations(context_node* parent, ConfigurationMap& theMap, const std::vector<cc_factory*>& availableFactories);
            void CreateContextTree(context_node* parent);
            std::string GetUniqueName();
            
            void LoadContents(context_node* node, std::vector<std::string>& compNames);
            void ExtractComponents(context_node* node, std::vector<config_string>& allComponents);
            void CreateComponents(const std::vector<config_string>& allConfigStrings, std::vector<std::string>& compNames);
            void SplitConfigs(const config_string& config, std::vector<config_string>& container);
            
            std::string CreateComponent(ConfigurationMap& theMap, const std::vector<cc_factory*>& availableFactories, const config_string& config);
            
            void PrintContexts(std::string name, context_node* parent);
            
            
            context_node* _Root;
            
            static constexpr char _ConfigurationBanner = '#';
            static constexpr char _ContextOpen = '{';
            static constexpr char _ContextClose = '}';
            
            const std::string _UniqueNameHeader = "cc_core_loader_unique_";
            int _UniqueNameIncrement = -1;
            
            /*
            enum ReadState
            {
                NewConfiguration = 0,
                ReadingConfiguration
            };
            
            void SetState(ReadState& currentState, ReadState& previousState);
            void FactoryWork(ConfigurationMap& myMap, const std::vector<cc_factory*>& availableFactories, const str_ConfigData& configData);
            bool LineContainsConfigurationBanner();
            void ReadConfigurationLine(str_ConfigData& configData);
            
            //TODO: AssignContents() does not allow these to have size > 1.
            
            
            int _SubConfigLevel;
            */
    };

}

#endif // CC_CORE_LOADER_H
