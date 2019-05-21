#include "core/comps/cc_mt19937.h"

#include <time.h>

#include "core/cc_config_helper.h"

namespace cc
{
    cc_mt19937::cc_mt19937(const std::string& name, const std::string& config) : cc_component(name, config)
    {
        //ctor
    }

    cc_mt19937::~cc_mt19937()
    {
        //dtor
    }

    bool cc_mt19937::Initialize(std::map<std::string, cc_component*>& availableComponents)
    {
        cc_component::Initialize(availableComponents);
        
        _Seed = time(0);
        ExtractSeed();
        seed(_Seed);
        
        return _IsValid;
    }
    
    void cc_mt19937::ExtractSeed()
    {
        std::string subContent;
        if(cc::GetSetting(_RawConfigurationData, "seed", subContent))
        {
            subContent = cc::GetFirstWord(subContent);
            if(cc::IsNumber(subContent))
            {
                subContent = cc::GetFirstWord(subContent);
                _Seed = cc::ConvertWord<size_t>(subContent);
                seed(_Seed);
            }
        }
    }
    
    size_t cc_mt19937::GetSeed()
    {
        return _Seed;
    }
}
