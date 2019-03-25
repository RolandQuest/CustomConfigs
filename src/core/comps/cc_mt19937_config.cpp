#include "core/comps/cc_mt19937.h"

#include <time.h>

#include "cc/cc_component.h"
#include "core/comps/cc_mt19937.h"
#include "core/comps/cc_mt19937_config.h"
#include "acc/cc_configuration_helper.h"

namespace cc
{
    cc_mt19937_config::cc_mt19937_config(const std::string& name, const std::string& rawData) : cc_component_configuration(name, rawData)
    {
        Seed = time(0);
        
        std::string contents;
        if(getSetting(rawData, "seed", contents))
        {
            std::string word = getFirstWord(contents);
            if(isNumber(word))
            {
                Seed = getNumber<size_t>(word);
            }
        }
    }

    cc_mt19937_config::~cc_mt19937_config()
    {
        //dtor
    }

    
    cc_component* cc_mt19937_config::Instantiate()
    {
        return new cc_mt19937(this, Seed);
    }
    
    bool cc_mt19937_config::Validate()
    {
        return true;
    }
    
    std::vector<std::string> cc_mt19937_config::GetReferenceNames()
    {
        std::vector<std::string> ret;
        return ret;
    }
}
