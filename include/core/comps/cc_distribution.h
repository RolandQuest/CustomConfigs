#ifndef CC_DISTRIBUTION_H
#define CC_DISTRIBUTION_H

#include <string>
#include <random>
#include <map>

#include "cc/cc_component.h"

namespace cc
{
    class cc_mt19937;
    
    class cc_distribution : public cc_component
    {

        public:

            cc_distribution(const std::string& name, const std::string& config);
            virtual ~cc_distribution();

            bool Initialize(std::map<std::string, cc_component*>& availableComponents) override;
            int Next();

        private:

            bool ExtractRngComponent(std::map<std::string, cc_component*>& availableComponents);
            bool ExtractDistribution();
            
            cc_mt19937* _Rando;
            std::discrete_distribution<int> _Dist;
    };

}

#endif // CC_DISTRIBUTION_H
