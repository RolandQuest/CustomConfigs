#ifndef CC_CORE_LOADER_H
#define CC_CORE_LOADER_H

#include <map>
#include <string>
#include <vector>
#include <set>

#include "cc/cc_loader.h"
#include "core/cc_base_loader.h"
#include "core/context_node.h"

namespace cc
{
    class cc_component;
    class cc_factory;
    typedef std::map<std::string, cc_component*> ComponentMap;
    
    class cc_core_loader : public cc_loader, public cc_base_loader
    {
        public:
            
            cc_core_loader();
            virtual ~cc_core_loader();
            
            bool Load(const std::string& configFile, ComponentMap& theMap, const std::set<cc_factory*>& availableFactories) override;
            
        private:
            
            std::vector<std::string> CreateConfigurations(context_node* parent, ComponentMap& theMap, const std::set<cc_factory*>& availableFactories);
            void CreateContextTree(context_node* parent);
            std::string GetUniqueName();
            
            void LoadContents(context_node* node, std::vector<std::string>& compNames);
            void ExtractComponents(context_node* node, std::vector<config_string>& allComponents);
            void CreateComponents(const std::vector<config_string>& allConfigStrings, std::vector<std::string>& compNames);
            void SplitConfigs(const config_string& config, std::vector<config_string>& container);
            
            std::string CreateComponent(ComponentMap& theMap, const std::set<cc_factory*>& availableFactories, const config_string& config);
            
            
            
            static constexpr char _ConfigurationBanner = '#';
            static constexpr char _ContextOpen = '{';
            static constexpr char _ContextClose = '}';
            
            const std::string _UniqueNameHeader = "cc_core_loader_unique_";
            int _UniqueNameIncrement = -1;
            
    };

}

#endif // CC_CORE_LOADER_H
