#ifndef CC_CONFIG_H
#define CC_CONFIG_H

#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "cc/cc_token.h"


/*


*/


namespace cc
{
	/**
	The configuration of all cc_component types. This is the components interface with the configuration loaded up by the set cc_loader.
	This is a temporary solution to get started. In the future, this class should be abstracted and inherited from.
	I have not figured out how to abstract the concept of configuration to the point you can create any type of configuration yet.
	This base class should also know nothing of cc_tokens.
	C++ does not support virtual template member functions, so that's out.
	*/
	class cc_config
	{

		public:

			//! Constructor
			cc_config() = default;

			//! Destructor
			virtual ~cc_config();

			//! Checks if string represents a double value.
			static bool IsDouble(const std::string& s);

			//! Checks if a string represents an integer value.
			static bool IsInteger(const std::string& s);

			//! Checks if a string represents an unsigned integer value.
			static bool IsUnsignedInteger(const std::string& s);

			//! Returns the first element of the setting.
			template<typename T>
			bool AsSingle(const std::string& name, T& container) const;

			//! Returns the kWord elements of the setting as a vector.
			template<typename T>
			bool AsVector(const std::string& name, std::vector<T>& container) const;

			//Returns the kWord elements of the setting as a 2d vector.
			/**
			Each line of the configuration will be a vector for the container (delimited by line breaks).
			If a line is empty, an emptry vector will NOT be inserted.
			*/
			template<typename T>
			bool As2dVector(const std::string& name, std::vector< std::vector<T> >& container) const;

			//! Returns a map object of the elements.
			/**
			The kWords provided should be in key, value order.
			As long as the setting is set up that way, std::ws is ignored.
			*/
			template<typename key, typename val>
			bool AsSingleMap(const std::string& name, std::map<key, val>& container) const;

			//! Returns a map of vector objects.
			/**
			Each line of the configuration will be a key, value pair.
			The code expects a key at the start of every line.
			*/
			template<typename key, typename val>
			bool AsVectorMap(const std::string& name, std::map< key, std::vector<val> >& container) const;

			//! Returns a token vector for component to consume how it sees fit.
			bool AsTokenVector(const std::string& name, cc_TokenVec& container) const;

			//! Insert data into settings
			bool InsertSettingData(const std::string& name, cc_kTokenVec& setting);

			//! Returns a vector of all setting names inserted.
			std::vector<std::string> ConfigDataKeys() const;

			//! Meta data in string form for printing out messages.
			std::vector<std::string> MetaData;

		private:

			//! Checks for a setting name.
			bool NameExists(const std::string& name) const;

			//! (config name -> config) Holds the configuration data.
			/**
			Need to determine who owns the cc_token pointers.
			Some entity has to know when they can be deleted.
			*/
			std::map<std::string, cc_TokenVec> _configData;
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

		std::vector<size_t> words = find_all_of(_configData.at(name), CoreToken::kWord);

		if (words.size() == 0) {
			return false;
		}

		std::stringstream ss;

		for (size_t i = 0; i < words.size(); i++) {
			ss.str(_configData.at(name)[words[i]]->value);
			ss.clear();

			T val;
			ss >> val;
			container.push_back(val);
		}
		
		return true;
	}

	//2d vector
	template<typename T>
	bool cc_config::As2dVector(const std::string& name, std::vector< std::vector<T> >& container) const {

		if (!NameExists(name)) {
			return false;
		}

		std::stringstream ss;
		std::vector<T> vec;
		T w;

		for (auto& word : _configData.at(name)) {

			if (word->type == CoreToken::kWord) {

				ss.str(word->value);
				ss.clear();

				ss >> w;
				vec.push_back(w);

				continue;
			}

			if (vec.size() > 0) {
				container.push_back(vec);
				vec.clear();
			}
		}

		return true;
	}

	//map -> single
	template<typename key, typename val>
	bool cc_config::AsSingleMap(const std::string& name, std::map<key, val>& container) const {

		if (!NameExists(name)) {
			return false;
		}

		std::stringstream ss;
		bool newEntry = true;
		key k;
		val v;

		for (auto& word : _configData.at(name)) {

			if (word->type == CoreToken::kWord) {

				ss.str(word->value);
				ss.clear();

				if (newEntry) {
					ss >> k;
					newEntry = false;
				}
				else {
					ss >> v;
					container[k] = v;
					newEntry = true;
				}
				continue;
			}
		}
		return true;
	}

	//map -> vector
	template<typename key, typename val>
	bool cc_config::AsVectorMap(const std::string& name, std::map< key, std::vector<val> >& container) const {

		if (!NameExists(name)) {
			return false;
		}

		std::stringstream ss;
		bool newEntry = true;
		key k;
		val v;
		std::vector<val> vec;

		for (auto& word : _configData.at(name)) {

			if (word->type == CoreToken::kWord) {

				ss.str(word->value);
				ss.clear();

				if (newEntry) {
					ss >> k;
					newEntry = false;
				}
				else {
					ss >> v;
					vec.push_back(v);
				}
				continue;
			}

			if (vec.size() > 0) {

				container[k] = vec;
				vec.clear();
			}
			newEntry = true;
		}

		return true;
	}
	

}

#endif