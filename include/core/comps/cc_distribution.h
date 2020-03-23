#ifndef CC_DISTRIBUTION_H
#define CC_DISTRIBUTION_H

#include <string>
#include <random>
#include <map>

#include "cc/cc_component.h"
#include "core/comps/cc_mt19937.h"

namespace cc
{
    class cc_distribution : public cc_component
    {

        public:

            bool cc_initialize(cc_ComponentMap& availableComponents) override;
            int Next();

        private:

            bool ExtractRngComponent(std::map<std::string, cc_component*>& availableComponents);
            bool ExtractDistribution();
            
            cc_mt19937* _Rando;
            std::discrete_distribution<int> _Dist;
    };

}

#endif // CC_DISTRIBUTION_H
