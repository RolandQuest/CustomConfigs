#ifndef CC_CORE_FACTORY_H
#define CC_CORE_FACTORY_H

#include <vector>
#include <string>

#include "cc/cc_factory.h"

namespace cc
{
    class cc_component_configuration;
    
    class cc_core_factory : public cc_factory
    {
        public:
            
            cc_core_factory();
            virtual ~cc_core_factory();
            
            std::vector<std::string> GetAvailableTypes() const override;
            bool ContainsType(std::string type) const override;
            cc_component_configuration* CreateConfiguration(const std::string& type, const std::string& name, const std::string& contents) const override;
            
        private:
            
            enum Type
            {
                DISTRIBUTION = 0,
                MT19937
            };
            
            const std::vector<std::string> Types = {
                "cc_distribution",
                "cc_rng"
            };
    };

}

#endif // CC_CORE_FACTORY_H
