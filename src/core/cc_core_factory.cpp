#include "core/cc_core_factory.h"

#include <exception>
#include <algorithm>

#include "cc/cc_component_configuration.h"
#include "core/comps/cc_distribution_config.h"
#include "core/comps/cc_mt19937_config.h"

namespace cc
{
    cc_core_factory::cc_core_factory()
    {
        //ctor
    }

    cc_core_factory::~cc_core_factory()
    {
        //dtor
    }
    
    std::vector<std::string> cc_core_factory::GetAvailableTypes()
    {
        return Types;
    }
    
    bool cc_core_factory::ContainsType(std::string type)
    {
        std::transform(std::begin(type),std::end(type),std::begin(type),::tolower);
        for(size_t i = 0; i < Types.size(); i++)
        {
            if(Types[i] == type)
            {
                return true;
            }
        }
        return false;
    }
    
    cc_component_configuration* cc_core_factory::CreateConfiguration(const std::string& type, const std::string& name, const std::string& contents)
    {
        //TODO: Change RNG to proper config.
        if(type == Types[DISTRIBUTION]) { return new cc_distribution_config(name, contents); }
        if(type == Types[MT19937])      { return new cc_mt19937_config(name, contents); }
        
        //TODO: Log problem.
        return nullptr;
    }
}
