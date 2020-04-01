#ifndef CC_MT19937_H
#define CC_MT19937_H

#include <string>
#include <map>
#include <random>

#include "cc/cc_component.h"

namespace cc
{
    //! A loadable mersenne twister rng
    class cc_mt19937 : public cc_component, public std::mt19937
    {
        public:
            
            //! Constructor
            cc_mt19937() = default;

            //! Destructor
            virtual ~cc_mt19937() = default;


            //!Initializes the component and linking names in the configuration with actual objects.
            bool cc_initialize(cc::cc_kComponentMap& availableComponents) override;

            //!Returns the type of the component.
            std::string cc_component_type() const;

            //! Returns the configuration of the component.
            const cc_config* const cc_component_config() const override;


            //! Returns the seed value being used.
            unsigned int GetSeed();
            
        private:
            
            unsigned int _Seed = 0;
        
    };

}

#endif // CC_MT19937_H
