#ifndef CC_BASE_DISTRIBUTION_H
#define CC_BASE_DISTRIBUTION_H

#include <string>
#include <random>
#include <map>

#include "cc/cc_component.h"
#include "core/comps/cc_mt19937.h"

namespace cc
{
    class cc_base_distribution : public cc_component
    {
        public:

            virtual bool cc_initialize(cc_kComponentMap& availableComponents) override;
            void SetRand(cc_mt19937* rando);

            virtual size_t Next() = 0;
            virtual size_t Size() = 0;
            virtual double GetWeightAtPosition(size_t position) = 0;

        protected:

            cc_mt19937* _Rando;

    };
}

#endif // CC_BASE_DISTRIBUTION_H
