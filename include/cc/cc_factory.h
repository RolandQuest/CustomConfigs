#ifndef CC_FACTORY_H
#define CC_FACTORY_H

#include <vector>
#include <string>

namespace cc
{
    class cc_component_configuration;
    
    class cc_factory
    {
        public:
            
            virtual ~cc_factory() = default;
            
            virtual std::vector<std::string> GetAvailableTypes() = 0;
            virtual bool ContainsType(std::string type) = 0;
            virtual cc_component_configuration* CreateConfiguration(const std::string& type, const std::string& name, const std::string& contents) = 0;
            
    };

}

#endif // CC_FACTORY_H
