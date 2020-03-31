#ifndef CC_CONFIG_HELPER_H
#define CC_CONFIG_HELPER_H

#include "cc/cclog.h"
#include "cc/cc_config.h"
#include "cc/cc_component.h"

#include <vector>
#include <set>
#include <sstream>
#include <string>

namespace cc
{
	//! Types of template typenames used for checking.
	enum class TemplateType : int
	{
		kDouble,
		kUnsignedDouble,
		kInt,
		kUnsigned,
		kBoolean,
		kString
	};

	/*
	All functions defined in the header file must be marked as inline or they'll be wrapped up
	into every components .obj file and you'll get linking issues.
	*/

	//! Checks if string represents a double value.
	inline bool IsDouble(const std::string& s) {

		if (s.empty() || (!std::isdigit(s[0]) && s[0] != '-' && s[0] != '+')) {
			return false;
		}

		char* p;
		std::strtod(s.c_str(), &p);

		return (*p == 0);
	}

	//! Checks if a string represents an integer value.
	inline bool IsInteger(const std::string& s) {

		if (s.empty() || (!std::isdigit(s[0]) && s[0] != '-' && s[0] != '+')) {
			return false;
		}

		char* p;
		std::strtol(s.c_str(), &p, 10);

		return (*p == 0);
	}

	//! Checks if a string represents an unsigned integer value.
	inline bool IsUnsignedInteger(const std::string& s) {

		if (IsInteger(s)) {
			return std::isdigit(s[0]) || s[0] == '+';
		}
		return false;
	}

	//! Validates a string matches the TemplateType.
	inline bool TemplateTypeCheck(const std::string& s, TemplateType t) {

		switch (t) {

			case TemplateType::kDouble:

				if (!IsDouble(s)) {
					cc::Log("TemplateTypeCheck: String does not match a double type.");
					return false;
				}
				return true;

			case TemplateType::kInt:
				
				if (!IsInteger(s)) {
					cc::Log("TemplateTypeCheck: String does not match an integer type.");
					return false;
				}
				return true;

			case TemplateType::kUnsigned:
				
				if (!IsUnsignedInteger(s)) {
					cc::Log("TemplateTypeCheck: String does not match an unsigned integer type.");
					return false;
				}
				return true;

			case TemplateType::kBoolean:

				if (s[0] != '0' && s[0] != '1') {
					cc::Log("TemplateTypeCheck: String does not match a boolean type (1 or 0).");
					return false;
				}
				return true;

			case TemplateType::kUnsignedDouble:

				if (!IsDouble(s) || s[0] == '-') {
					cc::Log("TemplateTypeCheck: String does not match a unsigned double type.");
					return false;
				}
				return true;
		}

		return true;
	}

	//! Finds component by name and returns the casted type pointer.
	template<typename CompType>
	bool ConvertToComponent(const std::string& compName, cc_kComponentMap& comps, CompType*& container) {

		if (comps.count(compName) == 0) {
			cc::Log("Could not find name, ", compName, ", listed in available components.");
			return false;
		}

		CompType* finalPointer = dynamic_cast<CompType*>(comps.at(compName));
		if (!finalPointer) {
			cc::Log("Could not cast found name, ", compName, ", to pointer type.");
			return false;
		}

		container = finalPointer;
		return true;
	}

	//! Returns the first element of the setting.
	template<typename T>
	bool AsSingle(const cc_config* config, const std::string& setName, T& container, TemplateType type = TemplateType::kString)  {

		cc_TokenVec tv;
		if (!config->TokenVector(setName, tv)) {
			return false;
		}

		int loc = find_first_of(tv, CoreToken::kWord);

		if (loc == -1) {
			return false;
		}

		if (!TemplateTypeCheck(tv[loc]->value, type)) {
			return false;
		}

		std::stringstream ss(tv[loc]->value);
		ss.clear();

		ss >> container;
		return true;
	}

	//! Returns the first element of the setting as a cc_component pointer.
	template<typename CompType>
	bool AsSingle(cc_config* config, const std::string& setName, CompType*& container, cc_kComponentMap& comps) {

		cc_TokenVec tv;
		if (!config->TokenVector(setName, tv)) {
			return false;
		}

		int loc = find_first_of(tv, CoreToken::kWord);

		if (loc == -1) {
			return false;
		}

		ConvertToComponent(tv[loc]->value, comps, container);
		return true;
	}

	//! Returns the kWord elements of the setting as a vector.
	template<typename T>
	bool AsVector(cc_config* config, const std::string& setName, std::vector<T>& container, TemplateType type = TemplateType::kString) {

		cc_TokenVec tv;
		if (!config->TokenVector(setName, tv)) {
			return false;
		}

		std::vector<size_t> words = find_all_of(tv, CoreToken::kWord);

		if (words.size() == 0) {
			return false;
		}

		for (auto& index : words) {
			if (!TemplateTypeCheck(tv[index]->value, type)) {
				return false;
			}
		}

		std::stringstream ss;

		for (size_t i = 0; i < words.size(); i++) {
			ss.str(tv[words[i]]->value);
			ss.clear();

			T val;
			ss >> val;
			container.push_back(val);
		}

		return true;
	}

	//! Returns the kWord elements of the setting as a vector of cc_component pointers.
	template<typename CompType>
	bool AsVector(cc_config* config, const std::string& setName, std::vector<CompType*>& container, cc_kComponentMap& comps) {

		cc_TokenVec tv;
		if (!config->TokenVector(setName, tv)) {
			return false;
		}

		std::vector<size_t> words = find_all_of(tv, CoreToken::kWord);

		if (words.size() == 0) {
			return false;
		}

		for (size_t i = 0; i < words.size(); i++) {

			CompType* p;
			if (ConvertToComponent(tv[words[i]]->value, comps, p)) {
				container.push_back(p);
			}
		}

		return true;
	}

	//! Returns the kWord elements of the setting as a set.
	template<typename T>
	bool AsSet(cc_config* config, const std::string& setName, std::set<T>& container, TemplateType type = TemplateType::kString) {

		cc_TokenVec tv;
		if (!config->TokenVector(setName, tv)) {
			return false;
		}

		std::vector<size_t> words = find_all_of(tv, CoreToken::kWord);

		if (words.size() == 0) {
			return false;
		}

		for (auto& index : words) {
			if (!TemplateTypeCheck(tv[index]->value, type)) {
				return false;
			}
		}

		std::stringstream ss;

		for (size_t i = 0; i < words.size(); i++) {
			ss.str(tv[words[i]]->value);
			ss.clear();

			T val;
			ss >> val;

			if (container.count(val) == 1) {
				cc::Log("Duplicate item found in set.");
				return false;
			}

			container.insert(val);
		}

		return true;
	}

	//! Returns the kWord elements of the setting as a set of cc_component pointers.
	template<typename CompType>
	bool AsSet(cc_config* config, const std::string& setName, std::set<CompType*>& container, cc_kComponentMap& comps) {

		cc_TokenVec tv;
		if (!config->TokenVector(setName, tv)) {
			return false;
		}

		std::vector<size_t> words = find_all_of(tv, CoreToken::kWord);

		if (words.size() == 0) {
			return false;
		}

		for (size_t i = 0; i < words.size(); i++) {

			CompType* p;
			if (ConvertToComponent(tv[words[i]]->value, comps, p)) {

				if (container.count(p) == 1) {
					cc::Log("Duplicate item found in set.");
					return false;
				}

				container.insert(p);
			}
		}

		return true;
	}
	
	//Returns the kWord elements of the setting as a 2d vector.
	/**
	Each line of the configuration will be a vector for the container (delimited by line breaks).
	If a line is empty, an emptry vector will NOT be inserted.
	*/
	template<typename T>
	bool As2dVector(cc_config* config, const std::string& setName, std::vector< std::vector<T> >& container, TemplateType type = TemplateType::kString) {

		cc_TokenVec tv;
		if (!config->TokenVector(setName, tv)) {
			return false;
		}

		for (auto& tok : tv) {
			if (tok->type == CoreToken::kWord) {
				if (!TemplateTypeCheck(tok->value, type)) {
					return false;
				}
			}
		}

		std::stringstream ss;
		std::vector<T> vec;
		T w;

		for (auto& word : tv) {

			if (word->type == CoreToken::kWord) {

				ss.str(word->value);
				ss.clear();

				ss >> w;
				vec.push_back(w);

				continue;
			}
			else if (word->type == CoreToken::kEndLine) {
				if (vec.size() > 0) {
					container.push_back(vec);
					vec.clear();
				}
			}
		}

		return true;
	}

	//Returns the kWord elements of the setting as a 2d vector of cc_component pointers.
	/**
	Each line of the configuration will be a vector for the container (delimited by line breaks).
	If a line is empty, an emptry vector will NOT be inserted.
	*/
	template<typename CompType>
	bool As2dVector(cc_config* config, const std::string& setName, std::vector< std::vector<CompType*> >& container, cc_kComponentMap& comps) {

		cc_TokenVec tv;
		if (!config->TokenVector(setName, tv)) {
			return false;
		}

		std::vector<CompType*> vec;

		for (auto& word : tv) {

			if (word->type == CoreToken::kWord) {

				CompType* p;
				if (ConvertToComponent(word->value, comps, p)) {
					vec.push_back(p);
				}
				continue;
			}
			else if (word->type == CoreToken::kEndLine && vec.size() > 0) {

				container.push_back(vec);
				vec.clear();
			}
		}

		return true;
	}

	//! Returns a map object of the elements.
	/**
	The kWords provided should be in key, value order.
	As long as the setting is set up that way, std::ws is ignored.
	*/
	template<typename key, typename val>
	bool AsSingleMap(cc_config* config, const std::string& setName, std::map<key, val>& container, TemplateType keyType, TemplateType valueType) {

		cc_TokenVec tv;
		if (!config->TokenVector(setName, tv)) {
			return false;
		}
			
		std::stringstream ss;
		bool newEntry = true;
		key k;
		val v;

		for (auto& word : tv) {

			if (word->type == CoreToken::kWord) {

				ss.str(word->value);
				ss.clear();

				if (newEntry) {

					if (!TemplateTypeCheck(word->value, keyType)) {
						return false;
					}

					ss >> k;
					newEntry = false;
				}
				else {

					if (!TemplateTypeCheck(word->value, valueType)) {
						return false;
					}

					ss >> v;
					container[k] = v;
					newEntry = true;
				}
				continue;
			}
		}
		return true;
	}

	//! Returns a map of vector objects.
	/**
	Each line of the configuration will be a key, value pair.
	The code expects a key at the start of every line.
	*/
	template<typename key, typename val>
	bool AsVectorMap(cc_config* config, const std::string& setName, std::map< key, std::vector<val> >& container, TemplateType keyType, TemplateType valueType) {

		cc_TokenVec tv;
		if (!config->TokenVector(setName, tv)) {
			return false;
		}
			
		std::stringstream ss;
		bool newEntry = true;
		key k;
		val v;
		std::vector<val> vec;

		for (auto& word : tv) {

			if (word->type == CoreToken::kWord) {

				ss.str(word->value);
				ss.clear();

				if (newEntry) {

					if (!TemplateTypeCheck(word->value, keyType)) {
						return false;
					}
					ss >> k;
					newEntry = false;
				}
				else {

					if (!TemplateTypeCheck(word->value, valueType)) {
						return false;
					}
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