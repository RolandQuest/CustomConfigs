#include "cc/cc_config.h"

namespace cc
{
	cc_config::~cc_config() {

		for (auto& setting : _configData) {
			for (auto& tok : setting.second) {
				delete tok;
			}
		}
	}

	bool cc_config::AsTokenVector(const std::string& name, cc_TokenVec& container) const
	{
		if (NameExists(name))
		{
			container = _configData.at(name);
			return true;
		}
		return false;
	}

	bool cc_config::InsertSettingData(const std::string& name, cc_kTokenVec& container)
	{
		if (!NameExists(name))
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

	bool cc_config::NameExists(const std::string& name) const
	{
		return _configData.find(name) != std::end(_configData);
	}

	bool cc_config::IsDouble(const std::string& s) {

		if (s.empty() || (!std::isdigit(s[0]) && s[0] != '-' && s[0] != '+')) {
			return false;
		}

		char* p;
		std::strtod(s.c_str(), &p);

		return (*p == 0);
	}
	bool cc_config::IsInteger(const std::string& s) {

		if (s.empty() || (!std::isdigit(s[0]) && s[0] != '-' && s[0] != '+')) {
			return false;
		}

		char* p;
		std::strtol(s.c_str(), &p, 10);

		return (*p == 0);
	}
	bool cc_config::IsUnsignedInteger(const std::string& s) {

		if (IsInteger(s)) {
			return std::isdigit(s[0]) || s[0] == '+';
		}
		return false;
	}

}

