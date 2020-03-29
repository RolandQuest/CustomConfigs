#ifndef CC_CORE_FACTORY_H
#define CC_CORE_FACTORY_H

#include <set>
#include <map>
#include <string>

#include "cc/cc_factory.h"
#include "cc/cc_config.h"
#include "cc/cc_component.h"

namespace cc
{
    class cc_core_factory : public cc_factory
    {
        public:
            
            cc_core_factory() = default;
            virtual ~cc_core_factory() = default;
            
            bool cc_contains_type(std::string type) const override;
            cc_component* cc_create_component(const std::string& type, const std::string& name, cc_config* config) const override;
            
    };

}

#endif // CC_CORE_FACTORY_H
