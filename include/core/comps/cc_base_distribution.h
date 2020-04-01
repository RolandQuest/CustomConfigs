#ifndef CC_BASE_DISTRIBUTION_H
#define CC_BASE_DISTRIBUTION_H

#include <string>
#include <random>
#include <map>

#include "cc/cc_component.h"
#include "core/comps/cc_mt19937.h"

namespace cc
{
    /**
        TODO: Implement a total weight function.
        TODO: Possibly rename size as it's weird.
    */
    //! Interface into distribution types.
    class cc_base_distribution : public cc_component
    {
        public:

            //!Initializes the component and linking names in the configuration with actual objects.
            bool cc_initialize(cc::cc_kComponentMap& availableComponents) override;


            //! Sets the rng to use.
            void SetRand(cc_mt19937* rando);

            //! Returns a number from the distribution.
            virtual size_t Next() = 0;

            //! Returns the size of the distribution.
            virtual size_t Size() = 0;

            //! Returns the weight at a given position.
            virtual double GetWeightAtPosition(size_t position) = 0;

        protected:

            //! The rng being used.
            cc_mt19937* _Rando;

    };
}

#endif // CC_BASE_DISTRIBUTION_H
