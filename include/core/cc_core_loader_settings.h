#ifndef CC_CORE_LOADER_SETTINGS_H
#define CC_CORE_LOADER_SETTINGS_H

#include <string>

#include "../cc/cc_token.h"

namespace cc
{
	//! Settings for the cc_core_loader.
	class cc_core_loader_settings
	{
		public:

			//! Constructor
			cc_core_loader_settings() = default;

			//! Destructor
			~cc_core_loader_settings() = default;


			/**
				Not implemented. Not 1 line of code.
				Well that's not true. It returns true always.
				That's gotta count for something.
			*/
			//! Validates that the settings won't cause easily avoidable issues.
			bool Validate();

			//! Returns the string reference for the given token type.
			std::string& operator[](CoreToken type);


			std::string ComponentBanner = "#";
			std::string SettingBanner = "&";
			std::string ContextOpen = "{";
			std::string ContextClose = "}";
			//std::string FunctionStart = ".";
			//std::string FunctionOpen = "(";
			//std::string FunctionClose = ")";
			//std::string FunctionParameterDelimiter = ",";

			bool EnableComments = true;
			std::string LineComment = "//";
			std::string BlockCommentStart = "/*";
			std::string BlockCommentEnd = "*/";

			std::string UniqueNameHeader = "cc_core_loader_unique_";
			std::string UniqueNameSignal = "??";

	};

}


#endif