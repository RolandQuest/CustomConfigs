#ifndef CC_UNIFORM_DISTRIBUTION_H
#define CC_UNIFORM_DISTRIBUTION_H

#include <string>
#include <random>
#include <map>

#include "cc/cc_component.h"
#include "core/comps/cc_base_distribution.h"

namespace cc
{

    class cc_uniform_distribution : public cc_base_distribution
    {
        public:

            cc_uniform_distribution() = default;
            cc_uniform_distribution(int size);
            virtual ~cc_uniform_distribution() = default;

            bool cc_initialize(cc_kComponentMap& availableComponents) override;
            std::string cc_type() const;

            virtual size_t Next() override;
            virtual size_t Size() override;
            virtual double GetWeightAtPosition(size_t position) override;

        protected:

            size_t _Size;
            std::uniform_int_distribution<size_t> _Dist;

    };

}

#endif // CC_UNIFORM_DISTRIBUTION_H
