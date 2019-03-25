#ifndef CC_MT19937_CONFIG_H
#define CC_MT19937_CONFIG_H

#include <string>
#include <vector>

#include "cc/cc_component_configuration.h"

namespace cc
{
    class cc_component;
    
    class cc_mt19937_config : public cc_component_configuration
    {
        public:
            
            cc_mt19937_config(const std::string& name, const std::string& rawData);
            virtual ~cc_mt19937_config();
            
            cc_component* Instantiate() override;
            bool Validate() override;
            std::vector<std::string> GetReferenceNames() override;
            
            //TODO: Possibly getters/setters?
            size_t Seed;
    };
}


#endif // CC_MT19937_CONFIG_H
