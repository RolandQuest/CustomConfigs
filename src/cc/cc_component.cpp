#include "cc/cc_component.h"

namespace cc
{
    cc_component::cc_component(const std::string& name, const std::string& config)
    {
        _ComponentName = name;
        _RawConfigurationData = config;
    }
    
    bool cc_component::Validate() const
    {
        return _IsValid && !_ComponentName.empty();
    }
    
    std::string cc_component::GetComponentName() const
    {
        return _ComponentName;
    }
}

