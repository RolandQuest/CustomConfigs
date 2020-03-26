#include "core/cc_core_factory.h"

#include <algorithm>

#include "cc/cclog.h"
//#include "core/comps/cc_distribution.h"
#include "core/comps/cc_mt19937.h"

namespace cc
{

    std::set<std::string> cc_core_factory::cc_available_types() const
    {
        std::set<std::string> types;
        for(auto& entry : Types)
        {
            types.insert(entry.first);
        }
        return types;
    }
    
    bool cc_core_factory::cc_contains_type(std::string type) const
    {
        std::transform(std::begin(type),std::end(type),std::begin(type),::tolower);
        return Types.count(type) == 1;
    }
    
    cc_component* cc_core_factory::cc_create_component(const std::string& type, const std::string& name, cc_config* config) const
    {
        std::string lcType = type;
        std::transform(std::begin(lcType),std::end(lcType),std::begin(lcType),::tolower);
        
        if (Types.count(lcType) == 0) {
            cc::Log(type, " 'type' not contained in call to cc_core_factory::CreateComponent().");
            return nullptr;
        }

        if (Types.at(lcType) == cccf_Type::kMT19937) {
            cc_mt19937* ret = new cc_mt19937();
            SetBasicData(ret, type, name, config);
            return ret;
        }

        //if(lcType == Types[DISTRIBUTION]) { return new cc_distribution(name, config); }


        cc::Log(type, " 'type' does not have a creation declaration in cc_core_factor::CreateComponent().");
        return nullptr;
    }
}
