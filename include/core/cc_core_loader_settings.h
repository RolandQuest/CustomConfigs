#ifndef CC_CORE_LOADER_SETTINGS_H
#define CC_CORE_LOADER_SETTINGS_H

#include <string>

#include "cc/cc_token.h"

namespace cc
{
	class cc_core_loader_settings
	{
		public:

			cc_core_loader_settings() = default;
			~cc_core_loader_settings() = default;

			bool Validate();
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