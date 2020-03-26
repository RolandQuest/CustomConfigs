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
    //! Base class for objects that do the heavy lifting of loading a configuration file into the cc portal.
    class cc_loader
    {
        public:
            
            //! Loads a configuration file into the provided component map.
            virtual bool cc_loader_load(const std::string& configFile, cc_ComponentMap& theMap, const cc_FactorySet& availableFactories) = 0;

            //! Serializes a component map into a configuration file.
            virtual void cc_loader_serialize(std::ostream& stream, cc_component* component) = 0;
    };
}


#endif // CC_LOADER_H
