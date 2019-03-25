#include "cc/cc_component_configuration.h"

namespace cc
{
    cc_component_configuration::cc_component_configuration(const std::string& name, const std::string& rawData)
    {
        Name = name;
        RawData = rawData;
    }
    
    std::string cc_component_configuration::GetName()
    {
        return Name;
    }
}
