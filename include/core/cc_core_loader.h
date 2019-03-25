#ifndef CC_CORE_LOADER_H
#define CC_CORE_LOADER_H

#include <map>
#include <string>
#include <vector>

#include "cc/cc_loader.h"
#include "acc/cc_base_loader.h"

namespace cc
{
    struct str_ConfigData
    {
        std::string Type = "";
        std::string Name = "";
        std::string Contents = "";
        
        bool IsValid()
        {
            return Type != "" && Name != "";
        }
        void Clear()
        {
            Type = "";
            Name = "";
            Contents = "";
        }
    };
    
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
            
            enum LineState
            {
                BeginFile = 0,
                NewConfiguration,
                ReadingConfiguration
            };
            
            void SetState(LineState& currentState, LineState& previousState);
            void FactoryWork(ConfigurationMap& myMap, const std::vector<cc_factory*>& availableFactories, const str_ConfigData& configData);
            bool LineContainsConfigurationBanner();
            void ReadConfigurationLine(str_ConfigData& configData);
            
            const std::string _ConfigurationBanner = "#";
    };

}

#endif // CC_CORE_LOADER_H
