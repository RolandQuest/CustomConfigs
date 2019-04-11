#include "core/comps/cc_mt19937.h"

#include <time.h>

#include "cc/cc_configuration_mapper.h"

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

    bool cc_mt19937::Initialize(std::map<std::string, cc_component*>& availableComponents, cc_configuration_mapper* configMapper)
    {
        _IsValid = true;
        _Seed = time(0);
        ExtractSeed(availableComponents, configMapper);
        seed(_Seed);
        return Validate();
    }
    
    void cc_mt19937::ExtractSeed(std::map<std::string, cc_component*>& availableComponents, cc_configuration_mapper* configMapper)
    {
        std::string subContent;
        if(configMapper->GetSetting(_RawConfigurationData, "seed", subContent))
        {
            subContent = configMapper->GetWord(subContent);
            if(configMapper->IsNumber(subContent))
            {
                subContent = configMapper->GetWord(subContent);
                _Seed = configMapper->ConvertWord<size_t>(subContent);
                seed(_Seed);
            }
        }
    }
    
    size_t cc_mt19937::GetSeed()
    {
        return _Seed;
    }
}
