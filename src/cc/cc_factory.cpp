#include "cc/cc_factory.h"

namespace cc
{

	void cc_factory::SetBasicData(cc_component* comp, const std::string& type, const std::string& name, cc_config* config) const {

		comp->cc_set_type(type);
		comp->cc_set_name(name);
		comp->cc_set_configuration(config);
	}
}
