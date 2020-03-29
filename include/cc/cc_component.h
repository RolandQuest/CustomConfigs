#ifndef CC_COMPONENT_H
#define CC_COMPONENT_H

#include <map>
#include <string>


#include "cc/cc_config.h"

namespace cc
{
    //To const or not to const, that is the question.
    const std::string _cc_default_name = "cc_default_name";

    
    class cc_component;
    //! For ease of use.
    using cc_ComponentMap = std::map<std::string, cc::cc_component*>;
    //! For ease of use.
    using cc_kComponentMap = const std::map<std::string, cc::cc_component*>;

    /**
    Base class for classes that can be loaded into the cc portal. 
    TODO: Implement clone method.
    */
    class cc_component
    {

        public:

            //!Constructor
            cc_component() = default;

            //!Virtual destructoooor!
            virtual ~cc_component();


            //! Initializes the component and linking names in the configuration with actual objects.
            /**
            I know what you're thinking. Why are we not passing the component map as a const? Right?
            Well because the components themselves may need to stand up a component and register it.
            Or do they... I'll leave it const for now.
            */
            virtual bool cc_initialize(cc_kComponentMap& availableComponents);


            //!Returns the component name used in the cc portal.
            const std::string& cc_component_name() const;


            //!Returns the type of the component.
            virtual std::string cc_component_type() const;


            //! Returns the configuration of the component.
            /**
            This is a virtual function so components may update their configuration before returning.
            It relieves a component from having to keep its configuration in sync with the state.
            */
            virtual const cc_config* const cc_component_config() const;


            //!Sets the name of the component.
            /**
            The name can only be set once. Consecutive calls will not change the name.
            The name of the component will be used by the cc portal.
            */
			void cc_set_name(std::string name);


            //! Sets the configuration of the component.
            /**
            The component will be switch its initialized status to false.
            */
			void cc_set_configuration(cc_config* config);


            //!Returns the initialized boolean.
            bool cc_is_initialized() const;
            

        protected:
            

			std::string _cc_name = _cc_default_name;
            cc_config* _cc_config = nullptr;
            bool _cc_is_initialized = false;

    };
}


#endif // CC_COMPONENT_H
