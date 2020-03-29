#ifndef CC_DISTRIBUTION_H
#define CC_DISTRIBUTION_H

#include <string>
#include <random>
#include <vector>
#include <map>

#include "cc/cc_component.h"
#include "core/comps/cc_base_distribution.h"

namespace cc
{
    class cc_discrete_distribution : public cc_base_distribution
    {

        public:

            cc_discrete_distribution() = default;
            virtual ~cc_discrete_distribution() = default;

            bool cc_initialize(cc_kComponentMap& availableComponents) override;
            std::string cc_type() const;

            virtual size_t Next() override;
            virtual size_t Size() override;
            virtual double GetWeightAtPosition(size_t position) override;

        protected:

            std::vector<double> _Weights;
            std::discrete_distribution<size_t> _Dist;

    };

}

#endif // CC_DISTRIBUTION_H
