#include "core/comps/cc_base_distribution.h"

#include "cc/cclog.h"
#include "cc/cc_config_helper.h"

namespace cc
{

    bool cc_base_distribution::cc_initialize(cc_kComponentMap& availableComponents)
    {
        cc_component::cc_initialize(availableComponents);

        _cc_is_initialized &= cc::AsSingle(_cc_config, "cc_rng", _Rando, availableComponents);

        return _cc_is_initialized;
    }

    void cc_base_distribution::SetRand(cc_mt19937* rando)
    {
        _Rando = rando;
    }

}

