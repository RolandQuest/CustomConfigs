#ifndef CC_DISTRIBUTION_H
#define CC_DISTRIBUTION_H

#include <vector>
#include <string>
#include <random>

#include "cc/cc_component.h"
#include "core/comps/cc_mt19937.h"

namespace cc
{
    class cc_mt19937;

    class cc_distribution : public cc_component
    {

        public:

            cc_distribution(cc_component_configuration* config, const std::vector<double>& rawData);
            virtual ~cc_distribution();

            bool Link(std::map<std::string, cc_component*>& availableComponents) override;
            int Next();

        private:

            cc_mt19937* RANDO;
            std::discrete_distribution<int> Dist;
    };

}

#endif // CC_DISTRIBUTION_H
