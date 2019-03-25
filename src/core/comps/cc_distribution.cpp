#include "core/comps/cc_distribution.h"

#include <algorithm>

#include "core/comps/cc_distribution_config.h"
#include "core/comps/cc_mt19937.h"
#include "cc/cc_component.h"

namespace cc
{
    cc_distribution::cc_distribution(cc_component_configuration* config, const std::vector<double>& rawData) : cc_component(config)
    {
        std::discrete_distribution<int> clone(std::begin(rawData), std::end(rawData));
        Dist = clone;
    }

    cc_distribution::~cc_distribution()
    {
        //dtor
    }
    
    bool cc_distribution::Link(std::map<std::string, cc_component*>& availableComponents)
    {
        std::string rngComp = static_cast<cc_distribution_config*>(Configuration)->cc_mt19937_Comp;
        
        if(availableComponents.count(rngComp) == 0)
        {
            return false;
        }
        
        cc_component* rando = availableComponents[rngComp];
        
        RANDO = static_cast<cc_mt19937*>(rando);
        return true;
    }

    int cc_distribution::Next()
    {
        return Dist(*RANDO);
    }
}
