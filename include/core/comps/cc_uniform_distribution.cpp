#include "core/comps/cc_uniform_distribution.h"

#include <vector>

#include "core/comps/cc_core_types.h"
#include "cc/cc_config_helper.h"

namespace cc
{
    cc_uniform_distribution::cc_uniform_distribution(int size) {

        _Size = size;
        std::uniform_int_distribution<size_t> temp(0, _Size - 1);
        _Dist = temp;
    }

    bool cc_uniform_distribution::cc_initialize(cc_kComponentMap& availableComponents) {

        cc_base_distribution::cc_initialize(availableComponents);

        _cc_is_initialized &= AsSingle(_cc_config, "size", _Size, TemplateType::kUnsigned);
        std::uniform_int_distribution<size_t> temp(0, _Size - 1);
        _Dist = temp;

        return _cc_is_initialized;
    }

    std::string cc_uniform_distribution::cc_type() const {
        return cc_uniform_dist_type;
    }

    size_t cc_uniform_distribution::Next()
    {
        return _Dist(*_Rando);
    }

    size_t cc_uniform_distribution::Size()
    {
        return _Size;
    }

    double cc_uniform_distribution::GetWeightAtPosition(size_t position)
    {
        return 1;
    }

}
