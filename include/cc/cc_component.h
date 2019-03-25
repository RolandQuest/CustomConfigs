#ifndef CC_COMPONENT_H
#define CC_COMPONENT_H

#include <map>
#include <string>

namespace cc
{
    class cc_component_configuration;
    
    class cc_component
    {
        public:
            
            cc_component(cc_component_configuration* config);
            virtual ~cc_component() = default;
            
            //TODO: Pass through as constant.
            virtual bool Link(std::map<std::string, cc_component*>& availableComponents) = 0;
            
        protected:
            
            cc_component_configuration* Configuration;
    };

}

#endif // CC_COMPONENT_H
