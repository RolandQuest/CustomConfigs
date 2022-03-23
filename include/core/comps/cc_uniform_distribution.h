#ifndef CC_UNIFORM_DISTRIBUTION_H
#define CC_UNIFORM_DISTRIBUTION_H

#include <string>
#include <random>
#include <map>

#include "../../cc/cc_component.h"
#include "cc_base_distribution.h"

namespace cc
{

    class cc_uniform_distribution : public cc_base_distribution
    {
        public:

            //! Constructor
            cc_uniform_distribution() = default;

            //! Constructor
            cc_uniform_distribution(int size);

            //! Destructor
            virtual ~cc_uniform_distribution() = default;


            //!Initializes the component and linking names in the configuration with actual objects.
            bool cc_initialize(cc::cc_kComponentMap& availableComponents) override;

            //!Returns the type of the component.
            std::string cc_component_type() const override;


            //! Returns a number from the distribution.
            size_t Next() override;

            //! Returns the size of the distribution.
            size_t Size() override;

            //! Returns the weight at a given position.
            double GetWeightAtPosition(size_t position) override;

        protected:

            size_t _Size;
            std::uniform_int_distribution<size_t> _Dist;

    };

}

#endif // CC_UNIFORM_DISTRIBUTION_H
