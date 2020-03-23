#ifndef CC_CORE_LOADER_TOKEN_H
#define CC_CORE_LOADER_TOKEN_H

#include <string>
#include <vector>

namespace cc
{
	enum class CoreToken : size_t
	{
		kComponentBanner = 0,
		kSettingBanner,
		kContextOpen,
		kContextClose,
		kLineComment,
		kBlockCommentStart,
		kBlockCommentEnd,
		kEndLine,
		kWord
	};

	class cc_token
	{
		public:

			cc_token(CoreToken t, const std::string& v) :type(t), value(v) {};
			~cc_token() = default;

			CoreToken type;
			std::string value;
	};

	int find_first_of(const std::vector<cc_token*>& tokenVec, CoreToken t);
	std::vector<size_t> find_all_of(const std::vector<cc_token*>& tokenVec, CoreToken t);

}

using cc_TokenVec = std::vector<cc::cc_token*>;
using cc_kTokenVec = const std::vector<cc::cc_token*>;
using cc_TokenVec2d = std::vector< std::vector<cc::cc_token*> >;
using cc_kTokenVec2d = const std::vector< std::vector<cc::cc_token*> >;

#endif