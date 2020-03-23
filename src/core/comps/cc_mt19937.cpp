#include "core/comps/cc_mt19937.h"

#include <time.h>

namespace cc
{

    bool cc_mt19937::cc_initialize(cc_kComponentMap& availableComponents)
    {
        cc_component::cc_initialize(availableComponents);
        
        _Seed = (unsigned int) time(0);

        std::string seedString;
        if (_cc_config->AsSingle("seed", seedString)) {

            if (cc_config::IsUnsignedInteger(seedString)) {

                _cc_config->AsSingle("seed", _Seed);
                seed(_Seed);
            }
        }

        _cc_config->MetaData.push_back("Seed used: " + std::to_string(_Seed));
        return true;
    }
    
    cc_config* cc_mt19937::cc_component_config() const {

        return _cc_config;
    }

    unsigned int cc_mt19937::GetSeed()
    {
        return _Seed;
    }
}
