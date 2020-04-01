#ifndef CC_COMPONENT_H
#define CC_COMPONENT_H

#include <map>
#include <string>

#include "cc/cc_config.h"

namespace cc
{
    /**
        To const or not to const, that is the question.
        Part of me likes the idea of the user being able to change it, but is that really necessary?
    */
    //! Default name for all cc_components.
    const std::string _cc_default_name = "cc_default_name";

    class cc_component;
    //! For ease of use.
    using cc_ComponentMap = std::map<std::string, cc::cc_component*>;
    //! For ease of use.
    using cc_kComponentMap = const std::map<std::string, cc::cc_component*>;

    /**
    Base class for objects that can be loaded and instantiated through the cc portal.

    TODO: Implement clone method as a pure virtual.
    */
    class cc_component
    {

        public:

            //!Constructor
            cc_component() = default;

            //!Virtual destructoooor!
            virtual ~cc_component();


            //! Initializes the component and linking names in the configuration with actual objects.
            virtual bool cc_initialize(cc_kComponentMap& availableComponents);

            //!Returns the component name used in the cc portal.
            const std::string& cc_component_name() const;

            //!Returns the type of the component.
            virtual std::string cc_component_type() const;

            /**
                This is a virtual function so components may update their configuration before returning.
                It relieves a component from having to keep its configuration in sync with the state.
            */
            //! Returns the configuration of the component.
            virtual const cc_config* const cc_component_config() const;

            /**
                The name can only be set once. Consecutive calls will not change the name.
                The name of the component will be used in the cc portal.
            */
            //!Sets the name of the component.
			void cc_set_name(std::string name);

            /**
                Calling will switch the components initialized state to false.
            */
            //! Sets the configuration of the component.
			void cc_set_configuration(cc_config* config);

            //!Returns the initialized boolean.
            bool cc_is_initialized() const;
            
        protected:
            
            //! The name of the component.
			std::string _cc_name = _cc_default_name;

            /*
                It is not guaranteed that the configuration is in sync with the component state.
                The cc_component_config() function is virtual for this reason.
            */
            //! The configuration of the component.
            cc_config* _cc_config = nullptr;

            //! Flag for successful cc_initialize(...) calls.
            bool _cc_is_initialized = false;

    };
}


#endif // CC_COMPONENT_H
