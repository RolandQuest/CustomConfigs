#ifndef CC_FACTORY_H
#define CC_FACTORY_H

#include <set>
#include <string>

#include "cc/cc_component.h"
#include "cc/cc_config.h"

namespace cc
{

    class cc_factory;
    //! For ease of use.
    using cc_FactorySet = std::set<cc::cc_factory*>;
    //! For ease of use.
    using cc_kFactorySet = const std::set<cc::cc_factory*>;

    /**
    Base class for the cc portal factory types used.
    Could perhaps be simplified a tad, but at least one of cc_available_types and cc_contains_type must be present.
    */
    class cc_factory
    {
        public:
            
            //! Checks to see if a type can be created using this factory.
            virtual bool cc_contains_type(std::string type) const = 0;

            //! Creates the component.
            virtual cc_component* cc_create_component(const std::string& type, const std::string& name, cc_config* config) const = 0;

        protected:

            //! Sets the basic data for a component. (Could possibly move to the portal.)
            void SetBasicData(cc_component* comp, const std::string& name, cc_config* config) const;

            //! To lower case
            void ToLower(std::string& lcType) const;

    };
}

#endif // CC_FACTORY_H
