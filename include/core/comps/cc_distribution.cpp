#include "core/comps/cc_distribution.h"

#include <vector>

#include "core/comps/cc_mt19937.h"
#include "cc/cclog.h"

namespace cc
{
    int cc_distribution::Next()
    {
        return _Dist(*_Rando);
    }
    
    bool cc_distribution::cc_initialize(std::map<std::string, cc_component*>& availableComponents)
    {
        cc_component::cc_initialize(availableComponents);
        
        _IsValid &= ExtractRngComponent(availableComponents);
        _IsValid &= ExtractDistribution();
        return _IsValid;
    }
    
    bool cc_distribution::ExtractRngComponent(std::map<std::string, cc_component*>& availableComponents)
    {
        std::string subContent;
        
        if(cc::GetSetting(_RawConfigurationData, "cc_rng", subContent))
        {
            subContent = cc::GetFirstWord(subContent);
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
    
    bool cc_distribution::ExtractDistribution()
    {
        std::string subContent;
        if(cc::GetSetting(_RawConfigurationData, "weights", subContent))
        {
            std::vector<std::string> rawWeights = cc::GetWordVector(subContent);
            std::vector<double> trueWeights = cc::ConvertVector<double>(rawWeights);
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
