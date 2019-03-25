#include "core/comps/cc_distribution_config.h"

#include "cc/cc_component.h"
#include "cc/cc_component_configuration.h"
#include "core/comps/cc_distribution.h"
#include "acc/cc_configuration_helper.h"
#include "core/comps/cc_distribution.h"

namespace cc
{
    cc_distribution_config::cc_distribution_config(const std::string& name, const std::string& rawData) : cc_component_configuration(name, rawData)
    {
        std::string settingContents;
        
        if(getSetting(rawData, "cc_rng", settingContents))
        {
            cc_mt19937_Comp = getFirstWord(settingContents);
        }
        if(getSetting(rawData, "weights", settingContents))
        {
            Weights = getVector<double>(settingContents);
        }
    }
    
    cc_distribution_config::~cc_distribution_config()
    {
        //dtor
    }
    
    cc_component* cc_distribution_config::Instantiate()
    {
        return new cc_distribution(this, Weights);
    }
    
    bool cc_distribution_config::Validate()
    {
        bool isSuccess = true;
        if(Weights.size() == 0)
        {
            isSuccess = false;
        }
        if(cc_mt19937_Comp == "")
        {
            isSuccess = false;
        }
        return isSuccess;
    }
    
    std::vector<std::string> cc_distribution_config::GetReferenceNames()
    {
        std::vector<std::string> ret = { cc_mt19937_Comp };
        return ret;
    }
}
