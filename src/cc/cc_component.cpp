#include "cc/cc_component.h"

namespace cc
{
    cc_component::cc_component(const std::string& name, const std::string& config)
    {
        _ComponentName = name;
        _RawConfigurationData = config;
    }
    
    bool cc_component::Initialize(std::map<std::string, cc_component*>& availableComponents)
    {
        _IsValid = true;
        return _IsValid;
    }
    
    bool cc_component::IsValid() const
    {
        return _IsValid;
    }
    
    const std::string& cc_component::GetComponentName() const
    {
        return _ComponentName;
    }
}

