#include "core/comps/cc_mt19937.h"

#include <time.h>

#include "cc/cc_config_helper.h"
#include "core/comps/cc_core_types.h"

namespace cc
{

    bool cc_mt19937::cc_initialize(cc_kComponentMap& availableComponents){

        cc_component::cc_initialize(availableComponents);

        _Seed = (unsigned int) time(0);

        if (_cc_config->KeyExists("seed")) {

            size_t setSeed;
            if (cc::AsSingle(_cc_config, "seed", setSeed, cc::TemplateType::kUnsigned)) {

                _Seed = setSeed;
            }
        }

        seed(_Seed);
        _cc_config->MetaData.push_back("Seed used: " + std::to_string(_Seed));

        return true;
    }

    std::string cc_mt19937::cc_component_type() const {
        return cc_rng_type;
    }

    const cc_config* const cc_mt19937::cc_component_config() const {
        return _cc_config;
    }

    unsigned int cc_mt19937::GetSeed(){
        return _Seed;
    }
}
