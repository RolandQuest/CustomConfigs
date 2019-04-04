#include "core/cc_core_factory.h"

#include <algorithm>

#include "cc/cclog.h"
#include "cc/cc_component.h"
#include "core/comps/cc_distribution.h"
#include "core/comps/cc_mt19937.h"

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
    
    std::set<std::string> cc_core_factory::GetAvailableTypes() const
    {
        std::set<std::string> types;
        for(const std::string& entry : Types)
        {
            types.insert(entry);
        }
        return types;
    }
    
    bool cc_core_factory::ContainsType(std::string type) const
    {
        std::transform(std::begin(type),std::end(type),std::begin(type),::tolower);
        return std::count(std::begin(Types),std::end(Types),type) != 0;
    }
    
    cc_component* cc_core_factory::CreateComponent(const std::string& type, const std::string& name, const std::string& config) const
    {
        std::string lcType = type;
        std::transform(std::begin(lcType),std::end(lcType),std::begin(lcType),::tolower);
        
        if(lcType == Types[DISTRIBUTION]) { return new cc_distribution(name, config); }
        if(lcType == Types[MT19937])      { return new cc_mt19937(name, config); }
        
        Log(type, " 'type' not found in call to cc_core_loader::CreateConfiguration().");
        return nullptr;
    }
}
