#include "cc/cc_factory.h"

#include <algorithm>

namespace cc
{

	void cc_factory::SetBasicData(cc_component* comp, const std::string& name, cc_config* config) const {

		comp->cc_set_name(name);
		comp->cc_set_configuration(config);
	}

	void cc_factory::ToLower(std::string& lcType) const {
		std::transform(std::begin(lcType), std::end(lcType), std::begin(lcType), ::tolower);
	}

}
