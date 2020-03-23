#ifndef CC_CONFIG_H
#define CC_CONFIG_H

#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "cc/cc_token.h"


/*

	Temporary solution!
	This class should be abstract!
	cc_Tokens should be abstract or only core.
	This class should know nothing about cc_tokens!

*/


namespace cc
{

	class cc_config
	{
		public:

			cc_config() = default;
			virtual ~cc_config();

			static bool IsDouble(const std::string& s);
			static bool IsInteger(const std::string& s);
			static bool IsUnsignedInteger(const std::string& s);

			//C++ does not support virtual template member functions.

			//single
			template<typename T>
			bool AsSingle(const std::string& name, T& container) const;

			//vector
			template<typename T>
			bool AsVector(const std::string& name, std::vector<T>& container) const;

			//2d vector
			template<typename T>
			bool As2dVector(const std::string& name, std::vector< std::vector<T> >& container) const;

			//map -> single
			template<typename key, typename val>
			bool AsSingleMap(const std::string& name, std::map<key, val>& container) const;

			//map -> vector
			template<typename key, typename val>
			bool AsVectorMap(const std::string& name, std::map< key, std::vector<val> >& container) const;

			//Raw token vector
			bool AsTokenVector(const std::string& name, cc_TokenVec& container) const;

			//Insert data into settings
			bool InsertSettingData(const std::string& name, cc_kTokenVec& setting);

			//Returns a vector of all keys in _configData inserted.
			std::vector<std::string> ConfigDataKeys() const;

			//Meta data in string form for printing out serialization information.
			std::vector<std::string> MetaData;

		private:

			bool NameExists(const std::string& name) const;

			//config name -> config
			std::map<std::string, cc_TokenVec> _configData;
			//Who owns these cc_token*?
	};

	
	//single
	template<typename T>
	bool cc_config::AsSingle(const std::string& name, T& container) const {

		if (!NameExists(name)) {
			return false;
		}

		int loc = find_first_of(_configData.at(name), CoreToken::kWord);

		if (loc == -1) {
			return false;
		}

		std::stringstream ss(_configData.at(name)[loc]->value);
		ss.clear();

		ss >> container;
		return true;
	}

	//vector
	template<typename T>
	bool cc_config::AsVector(const std::string& name, std::vector<T>& container) const {

		if (!NameExists(name)) {
			return false;
		}

		return true;
	}

	//2d vector
	template<typename T>
	bool cc_config::As2dVector(const std::string& name, std::vector< std::vector<T> >& container) const {

		if (!NameExists(name)) {
			return false;
		}

		return true;
	}

	//map -> single
	template<typename key, typename val>
	bool cc_config::AsSingleMap(const std::string& name, std::map<key, val>& container) const {

		if (!NameExists(name)) {
			return false;
		}

		return true;
	}

	//map -> vector
	template<typename key, typename val>
	bool cc_config::AsVectorMap(const std::string& name, std::map< key, std::vector<val> >& container) const {

		if (!NameExists(name)) {
			return false;
		}

		return true;
	}
	

}

#endif