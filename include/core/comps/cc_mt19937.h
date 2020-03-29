#ifndef CC_MT19937_H
#define CC_MT19937_H

#include <string>
#include <map>
#include <random>

#include "cc/cc_component.h"

namespace cc
{
    class cc_mt19937 : public cc_component, public std::mt19937
    {
        public:
            
            cc_mt19937() = default;
            virtual ~cc_mt19937() = default;

            const cc_config* const cc_component_config() const override;
            bool cc_initialize(cc_kComponentMap& availableComponents) override;
            std::string cc_type() const;

            unsigned int GetSeed();
            
        private:
            
            unsigned int _Seed = 0;
        
    };

}

#endif // CC_MT19937_H
