#ifndef CC_COMPONENT_H
#define CC_COMPONENT_H

#include <map>
#include <string>

namespace cc
{
    class cc_configuration_mapper;
    
    class cc_component
    {
        public:
            
            cc_component(const std::string& name, const std::string& config);
            virtual ~cc_component() = default;
            
            virtual bool Initialize(std::map<std::string, cc_component*>& availableComponents, cc_configuration_mapper* configMapper) = 0;
            virtual bool Validate() const;
            
        protected:
            
            std::string _RawConfigurationData;
            std::string _ComponentName;
            bool _IsValid = false;
    };

}

#endif // CC_COMPONENT_H
