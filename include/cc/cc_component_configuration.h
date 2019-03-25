#ifndef CC_COMPONENT_CONFIGURATION_H
#define CC_COMPONENT_CONFIGURATION_H

#include <string>
#include <vector>

namespace cc
{
    class cc_component;

    class cc_component_configuration
    {
        public:
            
            cc_component_configuration(const std::string& name, const std::string& rawData);
            virtual ~cc_component_configuration() = default;
            
            virtual cc_component* Instantiate() = 0;
            virtual bool Validate() = 0;
            virtual std::vector<std::string> GetReferenceNames() = 0;
            
            std::string GetName();
            
        protected:
            
            std::string Name;
            std::string RawData;
            
    };
}

#endif // CC_COMPONENT_CONFIGURATION_H
