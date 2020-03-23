#ifndef CC_LOADER_H
#define CC_LOADER_H

#include <ostream>
#include <string>
#include <map>
#include <set>

#include "cc/cc_factory.h"
#include "cc/cc_component.h"

namespace cc
{
    class cc_loader
    {
        public:
            
            virtual bool cc_loader_load(const std::string& configFile, cc_ComponentMap& theMap, const cc_FactorySet& availableFactories) = 0;
            virtual void cc_loader_serialize(std::ostream& stream, cc_component* component) = 0;
    };
}


#endif // CC_LOADER_H
