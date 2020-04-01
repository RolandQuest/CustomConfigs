#include "cc/cc_component.h"

namespace cc
{
	/*

	ctors/dtors

	*/

	cc_component::~cc_component() {
		delete _cc_config;
	}

	/*

	cc component

	*/

	void cc_component::cc_set_name(std::string name) {

		if (_cc_name == _cc_default_name) {
			_cc_name = name;
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

	std::string cc_component::cc_component_type() const {
		return "cc_component";
	}

	const cc_config* const cc_component::cc_component_config() const {
		return _cc_config;
	}

	bool cc_component::cc_initialize(cc_kComponentMap& availableComponents) {

		_cc_is_initialized = true;
		return true;
	}

}

