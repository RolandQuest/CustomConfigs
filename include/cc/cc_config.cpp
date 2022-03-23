#include "cc_config.h"

namespace cc
{
	cc_config::~cc_config() {

		for (auto& setting : _configData) {
			for (auto& tok : setting.second) {
				delete tok;
			}
		}
	}

	bool cc_config::TokenVector(const std::string& name, cc_TokenVec& container) const
	{
		if (KeyExists(name))
		{
			container = _configData.at(name);
			return true;
		}
		return false;
	}

	bool cc_config::InsertSettingData(const std::string& name, cc_kTokenVec& container)
	{
		if (!KeyExists(name))
		{
			_configData[name] = container;
			return true;
		}
		return false;
	}

	std::vector<std::string> cc_config::ConfigDataKeys() const {

		std::vector<std::string> ret;
		for (auto& entry : _configData) {
			ret.push_back(entry.first);
		}
		return ret;
	}

	bool cc_config::KeyExists(const std::string& name) const {
		return _configData.find(name) != std::end(_configData);
	}

}

