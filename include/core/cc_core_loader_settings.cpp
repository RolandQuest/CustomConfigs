#include "cc_core_loader_settings.h"

#include "../cc/cclog.h"

namespace cc
{
	bool cc_core_loader_settings::Validate() {

		//TODO: Ensure the symbols chosen to signify tokens:
		//			1. Do not contain the same characters as this could be confusing.
		//			2. Are not empty strings.
		//			3. Do not contain whitespace.
		//			4. Are not the same.
		//		Log all problems through he cc logger then return false.

		return true;
	}

	std::string& cc_core_loader_settings::operator[](CoreToken type) {

		switch (type) {

			case CoreToken::kComponentBanner:
				return ComponentBanner;

			case CoreToken::kSettingBanner:
				return SettingBanner;

			case CoreToken::kContextOpen:
				return ContextOpen;

			case CoreToken::kContextClose:
				return ContextClose;

			case CoreToken::kLineComment:
				return LineComment;

			case CoreToken::kBlockCommentStart:
				return BlockCommentStart;

			case CoreToken::kBlockCommentEnd:
				return BlockCommentEnd;

			default:
				cc::Log("cc_core_loader_settings::operator[] - Unable to find CoreToken type.");
				return BlockCommentEnd;
		}

	}

}
