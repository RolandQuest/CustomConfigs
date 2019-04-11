#include "core/comps/cc_distribution.h"

#include <vector>

#include "core/comps/cc_mt19937.h"
#include "cc/cc_configuration_mapper.h"
#include "cc/cclog.h"

namespace cc
{
    cc_distribution::cc_distribution(const std::string& name, const std::string& config) : cc_component(name, config)
    {
        
    }

    cc_distribution::~cc_distribution()
    {
        //dtor
    }
    
    int cc_distribution::Next()
    {
        return _Dist(*_Rando);
    }
    
    bool cc_distribution::Initialize(std::map<std::string, cc_component*>& availableComponents, cc_configuration_mapper* configMapper)
    {
        _IsValid = true;
        _IsValid &= ExtractRngComponent(availableComponents, configMapper);
        _IsValid &= ExtractDistribution(configMapper);
        return Validate();
    }
    
    bool cc_distribution::ExtractRngComponent(std::map<std::string, cc_component*>& availableComponents, cc_configuration_mapper* configMapper)
    {
        std::string subContent;
        
        if(configMapper->GetSetting(_RawConfigurationData, "cc_rng", subContent))
        {
            subContent = configMapper->GetWord(subContent);
            if(availableComponents.count(subContent) != 0)
            {
                if(cc_mt19937* finalPointer = dynamic_cast<cc_mt19937*>(availableComponents[subContent]))
                {
                    _Rando = finalPointer;
                    return true;
                }
                else
                {
                    Log("Component '", _ComponentName, "': Reference to cc_rng could not be cast as cc_rng.");
                }
            }
            else
            {
                Log("Component '", _ComponentName, "': References unknown cc_rng name:", subContent);
            }
        }
        else
        {
            Log("Component '", _ComponentName, "': No associated cc_rng object.");
        }
        
        
        return false;
    }
    
    bool cc_distribution::ExtractDistribution(cc_configuration_mapper* configMapper)
    {
        std::string subContent;
        if(configMapper->GetSetting(_RawConfigurationData, "weights", subContent))
        {
            std::vector<std::string> rawWeights = configMapper->GetWordVector(subContent);
            std::vector<double> trueWeights = configMapper->ConvertVector<double>(rawWeights);
            if(trueWeights.size() != 0)
            {
                std::discrete_distribution<int> clone(std::begin(trueWeights), std::end(trueWeights));
                _Dist = clone;
                return true;
            }
            else
            {
                Log("Component '", _ComponentName, "': Extracted weights setting contained zero numbers.");
            }
        }
        else
        {
            Log("Component '", _ComponentName, "': Could not extract weights.");
        }
        
        return false;
    }
    
}
