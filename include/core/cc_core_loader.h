#ifndef CC_CORE_LOADER_H
#define CC_CORE_LOADER_H

#include <map>
#include <string>
#include <vector>
#include <ostream>
#include <set>

#include "../cc/cc_component.h"
#include "../cc/cc_factory.h"
#include "../cc/cc_loader.h"
#include "../cc/cc_token.h"
#include "../cc/cc_config.h"
#include "cc_core_loader_settings.h"

namespace cc
{
    //! A provided cc loader courtesy cc portal. =)
    class cc_core_loader : public cc_loader
    {
        public:
            
            //! Constructor
            cc_core_loader() = default;

            //! Destructor
            virtual ~cc_core_loader() = default;
            

            //! Loads a configuration files components and stores them into the provided map.
            bool cc_loader_load(const std::string& configFile, cc_ComponentMap& theMap, cc_kFactorySet& availableFactories) override;

            //! Serializes a component into the provided stream.
            void cc_loader_serialize(std::ostream& stream, cc_component* component) override;

            //! Settings for changing how the loader views tokens.
			cc_core_loader_settings settings;

        private:
            
            cc_config* GenerateConfig(cc_TokenVec& comp);
            void CreateComponents(cc_ComponentMap& theMap, cc_kFactorySet& availableFactories, cc_TokenVec2d& components);
            void ConstructComponents(cc_TokenVec2d& contexts, cc_TokenVec2d& components);
            cc_TokenVec ConstructContexts(cc_TokenVec& allTokens, cc_TokenVec2d& contexts, size_t& pos, size_t& contextLevel);
            void ClearComments(cc_TokenVec& allTokens);
            bool LoadTokens(const std::string& configFile, cc_TokenVec& allTokens);
            void DelimitWord(const std::string& word, cc_TokenVec& allTokens);
    };

}

#endif // CC_CORE_LOADER_H
