#ifndef CC_CONFIG_H
#define CC_CONFIG_H

#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "cc/cc_token.h"

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

			//! Insert data into settings
			bool InsertSettingData(const std::string& name, cc_kTokenVec& setting);

			//! Returns a vector of all setting names inserted.
			std::vector<std::string> ConfigDataKeys() const;

			//! Checks for a setting name.
			bool KeyExists(const std::string& name) const;

			//! Returns a token vector for component to consume how it sees fit.
			bool TokenVector(const std::string& name, cc_TokenVec& container) const;

			//! Meta data in string form for printing out comments on serializing.
			std::vector<std::string> MetaData;

		private:

			/**
				Need to determine who owns the cc_token pointers.
				Some entity has to know when they can be deleted.
			*/
			//! (config name -> config) Holds the configuration data.
			std::map<std::string, cc_TokenVec> _configData;
	};

}

#endif