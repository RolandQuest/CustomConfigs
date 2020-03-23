#ifndef CC_FACTORY_H
#define CC_FACTORY_H

#include <set>
#include <string>

#include "cc/cc_component.h"
#include "cc/cc_config.h"

namespace cc
{
    class cc_factory
    {
        public:
            
            virtual std::set<std::string> cc_available_types() const = 0;
            virtual bool cc_contains_type(std::string type) const = 0;
            virtual cc_component* cc_create_component(const std::string& type, const std::string& name, cc_config* config) const = 0;

        protected:

            void SetBasicData(cc_component* comp, const std::string& type, const std::string& name, cc_config* config) const;
    };
}

using cc_FactorySet = std::set<cc::cc_factory*>;
using cc_kFactorySet = const std::set<cc::cc_factory*>;

#endif // CC_FACTORY_H
