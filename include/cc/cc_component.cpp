#include "cc/cc_component.h"

namespace cc
{

	cc_component::~cc_component() {

		delete _cc_config;
	}

	void cc_component::cc_set_name(std::string name) {

		if (_cc_name == _cc_default_name) {
			_cc_name = name;
		}
	}

	void cc_component::cc_set_type(std::string type) {

		if (_cc_type == _cc_default_name) {
			_cc_type = type;
		}
	}

	void cc_component::cc_set_configuration(cc_config* config) {

		_cc_config = config;
		_cc_is_initialized = false;
	}

	bool cc_component::cc_is_initialized() const {

		return _cc_is_initialized;
	}

	const std::string& cc_component::cc_component_name() const {

		return _cc_name;
	}

	const std::string& cc_component::cc_component_type() const {

		return _cc_type;
	}

	const cc_config* const cc_component::cc_component_config() const {

		return _cc_config;
	}

	bool cc_component::cc_initialize(const std::map<std::string, cc::cc_component*>& availableComponents) {

		_cc_is_initialized = true;
		return true;
	}

}

