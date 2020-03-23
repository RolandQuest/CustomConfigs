#ifndef CC_COMPONENT_H
#define CC_COMPONENT_H

#include <map>
#include <string>

#include "cc/cc_config.h"

namespace cc
{
    //To const or not to const, that is the question.
    const std::string _cc_default_name = "cc_default_name";

    class cc_component
    {
        public:
            
            virtual ~cc_component();

			void cc_set_name(std::string name);
			void cc_set_type(std::string type);
			void cc_set_configuration(cc_config* config);
			const std::string& cc_component_name() const;
			const std::string& cc_component_type() const;
            virtual cc_config* cc_component_config() const = 0;
            virtual bool cc_initialize(const std::map<std::string, cc::cc_component*>& availableComponents);
            bool cc_is_initialized() const;
            
            //Clone somehow


        protected:
            
            std::string _cc_type = _cc_default_name;
			std::string _cc_name = _cc_default_name;
            cc_config* _cc_config = nullptr;
            bool _cc_is_initialized = false;

    };
}

using cc_ComponentMap = std::map<std::string, cc::cc_component*>;
using cc_kComponentMap = const std::map<std::string, cc::cc_component*>;

#endif // CC_COMPONENT_H
