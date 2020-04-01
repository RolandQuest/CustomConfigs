#ifndef CC_CORE_LOADER_TOKEN_H
#define CC_CORE_LOADER_TOKEN_H

#include <string>
#include <vector>

namespace cc
{
	
	class cc_token;
	//! For ease of use.
	using cc_TokenVec = std::vector<cc::cc_token*>;
	//! For ease of use.
	using cc_kTokenVec = const std::vector<cc::cc_token*>;
	//! For ease of use.
	using cc_TokenVec2d = std::vector< std::vector<cc::cc_token*> >;
	//! For ease of use.
	using cc_kTokenVec2d = const std::vector< std::vector<cc::cc_token*> >;

	/**
		kWord and kEndLine are the only tokens stored in configurations.
		All others are used for parsing the configuration files.
	*/
	//! Enumeration of token types.
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

	//! A token respresenting a word, symbol, or number read in by the loader.
	class cc_token
	{
		public:

			//! Constructor
			cc_token(CoreToken t, const std::string& v) :type(t), value(v) {};

			//! Destructor
			~cc_token() = default;


			//! The token type
			CoreToken type;

			//! The string representation of the token.
			std::string value;
	};

	//! Finds the first matching token type of a vector of tokens. Returns -1 in the event none are found.
	int find_first_of(cc_kTokenVec& tokenVec, CoreToken t);

	//! Finds the positions of all matching tokens types of the provided vector.
	std::vector<size_t> find_all_of(cc_kTokenVec& tokenVec, CoreToken t);

}

#endif