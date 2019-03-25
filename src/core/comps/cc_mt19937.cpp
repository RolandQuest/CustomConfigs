#include "core/comps/cc_mt19937.h"

#include "cc/cc_component.h"
#include "cc/cc_component_configuration.h"
#include "core/comps/cc_mt19937_config.h"

namespace cc
{
    cc_mt19937::cc_mt19937(cc_component_configuration* config, const size_t& Seed) : cc_component(config)
    {
        seed(Seed);
    }

    cc_mt19937::~cc_mt19937()
    {
        //dtor
    }

    bool cc_mt19937::Link(std::map<std::string, cc_component*>& availableComponents)
    {
        return true;
    }
}
