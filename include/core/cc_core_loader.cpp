#include "core/cc_core_loader.h"

#include <sstream>
#include <algorithm>

#include "cc/ccportal.h"
#include "cc/cclog.h"

namespace cc
{

	namespace
	{
		const std::vector<CoreToken> _CoreDelimiters = {
			CoreToken::kComponentBanner,
			CoreToken::kSettingBanner,
			CoreToken::kContextOpen,
			CoreToken::kContextClose
		};
		const std::vector<CoreToken> _CommentDelimiters = {
			CoreToken::kLineComment,
			CoreToken::kBlockCommentStart,
			CoreToken::kBlockCommentEnd
		};

	}

	void cc_core_loader::cc_loader_serialize(std::ostream& stream, cc_component* component) {

		const cc_config* const config = component->cc_component_config();
		std::vector<std::string> keys = config->ConfigDataKeys();

		if (settings.EnableComments) {

			for (auto& data : config->MetaData) {
				stream << settings.LineComment << data << '\n';
			}
		}

		stream << settings.ComponentBanner << component->cc_component_type() << '\t' << component->cc_component_name() << '\n';

		for (auto& key : keys) {

			stream << '\t' << settings.SettingBanner << key << '\t';

			cc_TokenVec vec;
			config->TokenVector(key, vec);

			for (auto& tok : vec) {
				stream << '\t' << tok->value;
			}
			stream << '\n';
		}
	}

    bool cc_core_loader::cc_loader_load(const std::string& configFile, cc_ComponentMap& theMap, cc_kFactorySet& availableFactories)
    {
		cc_TokenVec allTokens;
		allTokens.reserve(2000);

		if (!LoadTokens(configFile, allTokens)) {
			return false;
		}

		ClearComments(allTokens);

		cc_TokenVec2d contexts;
		size_t pos = 0, contextLevel = 0;
		ConstructContexts(allTokens, contexts, pos, contextLevel);

		if (contextLevel > 0) {
			cc::Log("Context level ended at ", contextLevel, ". Careful when not closing contexts.");
		}

		cc_TokenVec2d components;
		ConstructComponents(contexts, components);

		CreateComponents(theMap, availableFactories, components);

        return true;
    }

	void cc_core_loader::CreateComponents(cc_ComponentMap& theMap, cc_kFactorySet& availableFactories, cc_TokenVec2d& components) {

		for (auto comp : components) {

			std::string 
				type = comp[0]->value,
				name = comp[1]->value;

			if (theMap.count(name) == 1) {
				cc::Log("File has duplicate component names. Ignoring second.");

				for (auto& tok : comp) {
					delete tok;
				}
				continue;
			}

			delete comp[0];
			delete comp[1];
			comp.erase(std::begin(comp), std::begin(comp) + 2);

			cc_config* config = GenerateConfig(comp);

			for (auto& fact : availableFactories) {

				if (fact->cc_contains_type(type)) {

					cc_component* c = fact->cc_create_component(type, name, config);
					theMap[name] = c;
					break;
				}
			}
		}
	}

	cc_config* cc_core_loader::GenerateConfig(cc_TokenVec& comp) {

		cc_config* config = new cc_config();

		std::vector<size_t> bannerLocs = find_all_of(comp, CoreToken::kSettingBanner);

		if (bannerLocs.size() == 0) {
			return config;
		}

		for (size_t i = 0; i < bannerLocs[0]; i++) {
			delete comp[i];
		}

		for (size_t bli = 0; bli < bannerLocs.size(); bli++) {

			delete comp[bannerLocs[bli]];

			size_t eosIndex = (bli == bannerLocs.size() - 1) ? comp.size() : bannerLocs[bli + 1];

			if (eosIndex - bannerLocs[bli] - 1 < 2) {
				cc::Log("Empty setting found!");
				continue;
			}

			if (comp[bannerLocs[bli] + 1]->type != CoreToken::kWord) {
				cc::Log("Setting name not set as kWord token type.");
				continue;
			}

			cc_TokenVec settingInfo;
			std::string settingName = comp[bannerLocs[bli] + 1]->value;
			delete comp[bannerLocs[bli] + 1];
			
			for (size_t si = bannerLocs[bli] + 2; si < eosIndex; si++) {
				settingInfo.push_back(comp[si]);
			}

			config->InsertSettingData(settingName, settingInfo);
		}

		return config;
	}

	void cc_core_loader::ConstructComponents(cc_TokenVec2d& contexts, cc_TokenVec2d& components) {

		for (auto& context : contexts) {

			std::vector<cc_token*> comp;
			std::vector<size_t> bannerLocs = find_all_of(context, CoreToken::kComponentBanner);

			if (bannerLocs.size() == 0) {
				cc::Log("Context found with no components defined.");

				for (size_t i = 0; i < context.size(); i++) {
					delete context[i];
				}
				return;
			}

			for (size_t i = 0; i < bannerLocs[0]; i++) {
				delete context[i];
			}

			for (size_t bpi = 0; bpi < bannerLocs.size(); bpi++) {

				delete context[bannerLocs[bpi]];

				cc_TokenVec comp;
				size_t eocIndex = (bpi == bannerLocs.size() - 1) ? context.size() : bannerLocs[bpi + 1];
				
				for (size_t ti = bannerLocs[bpi] + 1; ti < eocIndex; ti++) {
					comp.push_back(context[ti]);
				}

				if (comp.size() < 2) {
					cc::Log("Component found with size less than 2 tokens. A type and name must be provided.");
					continue;
				}

				if (comp[0]->type != CoreToken::kWord || comp[1]->type != CoreToken::kWord) {
					cc::Log("Component found with type or name not logged as a kWord token type.");
					continue;
				}

				components.push_back(comp);
			}
		}
	}

	cc_TokenVec cc_core_loader::ConstructContexts(cc_TokenVec& allTokens, cc_TokenVec2d& contexts, size_t& pos, size_t& contextLevel) {

		cc_TokenVec context, names;

		for (; pos < allTokens.size(); pos++) {

			CoreToken ctype = allTokens[pos]->type;

			if (ctype == CoreToken::kContextOpen) {

				delete allTokens[pos];
				allTokens.erase(std::begin(allTokens) + pos);

				cc_TokenVec subNames = ConstructContexts(allTokens, contexts, pos, ++contextLevel);
				context.insert(std::end(context), std::begin(subNames), std::end(subNames));
			}

			else if (ctype == CoreToken::kContextClose) {

				delete allTokens[pos];
				allTokens.erase(std::begin(allTokens) + pos);
				pos--;

				if (contextLevel == 0) {
					cc::Log("Full context closed! Rest of file will not be loaded!");
				}
				else {
					contextLevel--;
				}

				break;
			}

			else if (ctype == CoreToken::kComponentBanner) {

				context.push_back(allTokens[pos]);
				if (pos + 2 < allTokens.size()) {

					if (allTokens[pos + 2]->type != CoreToken::kWord || allTokens[pos + 1]->type != CoreToken::kWord) {
						cc::Log("Invalid configuration. The two tokens following a component banner must both be words.");
					}
					names.push_back(allTokens[pos + 2]);
				}
			}

			else {

				context.push_back(allTokens[pos]);
			}

		}

		contexts.push_back(context);
		return names;
	}

	void cc_core_loader::ClearComments(cc_TokenVec& allTokens) {

		bool inBlockComment = false;
		bool inLineComment = false;

		for (size_t i = 0; i < allTokens.size(); i++) {

			bool eraseMe = false;

			if (inLineComment) {
				eraseMe = true;
				if (allTokens[i]->type == CoreToken::kEndLine) {
					inLineComment = false;
				}
			}
			else if (inBlockComment) {
				eraseMe = true;
				if (allTokens[i]->type == CoreToken::kBlockCommentEnd) {
					inBlockComment = false;
				}
			}
			else if (allTokens[i]->type == CoreToken::kLineComment) {
				eraseMe = true;
				inLineComment = true;
			}
			else if (allTokens[i]->type == CoreToken::kBlockCommentStart) {
				eraseMe = true;
				inBlockComment = true;
			}

			if (eraseMe) {
				delete allTokens[i];
				allTokens.erase(std::begin(allTokens) + i);
				i--;
			}
		}

		if (inBlockComment) {
			cc::Log("Block comment reached end of file without closing. Careful!");
		}

	}

	bool cc_core_loader::LoadTokens(const std::string& configFile, cc_TokenVec& allTokens) {

		std::ifstream stream(configFile);
		if (!stream.is_open()) {
			cc::Log("Could not open file ", configFile, ". Maybe it doesn't exist?");
			return false;
		}

		std::string line;
		while (std::getline(stream, line))
		{
			std::stringstream ss(line);
			ss.clear();

			while (!(ss >> std::ws).eof())
			{
				std::string word;
				ss >> word;

				DelimitWord(word, allTokens);
			}

			allTokens.push_back(new cc_token(CoreToken::kEndLine, "\n"));
		}

		stream.close();
		return true;
	}

	void cc_core_loader::DelimitWord(const std::string& word, cc_TokenVec& allTokens) {

		if (word.empty()) {
			return;
		}

		size_t posOfFirstDelimit = std::string::npos;
		CoreToken tokenType;

		for (size_t i = 0; i < _CoreDelimiters.size(); i++) {

			size_t pos = word.find(settings[_CoreDelimiters[i]]);
			if (pos < posOfFirstDelimit) {
				posOfFirstDelimit = pos;
				tokenType = _CoreDelimiters[i];
			}
			if (posOfFirstDelimit == 0) {
				//Potential optimization
				break;
			}
		}

		if (settings.EnableComments)
		{
			for (size_t i = 0; i < _CommentDelimiters.size(); i++) {

				size_t pos = word.find(settings[_CommentDelimiters[i]]);
				if (pos < posOfFirstDelimit) {
					posOfFirstDelimit = pos;
					tokenType = _CommentDelimiters[i];
				}
				if (posOfFirstDelimit == 0) {
					//Potential optimization
					break;
				}
			}
		}

		if (posOfFirstDelimit == std::string::npos) {

			allTokens.push_back(new cc_token(CoreToken::kWord, word));
			return;
		}
		else if (posOfFirstDelimit == 0) {

			allTokens.push_back(new cc_token(tokenType, settings[tokenType]));
			DelimitWord(word.substr(settings[tokenType].size(), std::string::npos), allTokens);
		}
		else {
			allTokens.push_back(new cc_token(CoreToken::kWord, word.substr(0, posOfFirstDelimit)));
			allTokens.push_back(new cc_token(tokenType, settings[tokenType]));
			DelimitWord(word.substr(posOfFirstDelimit + settings[tokenType].size(), std::string::npos), allTokens);
		}

	}

}
