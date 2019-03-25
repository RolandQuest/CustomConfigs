#ifndef CCPORTAL_H
#define CCPORTAL_H

#include <map>
#include <string>
#include <vector>

namespace cc
{
    class cc_component_configuration;
    class cc_factory;
    class cc_loader;
    class cc_component;
    
    typedef std::map<std::string, cc_component_configuration*> ConfigurationMap;
    typedef std::map<std::string, cc_component*> ComponentMap;
    
    bool load(const std::string& configFile);
    cc_loader* setLoader(cc_loader* loader);
    cc_factory* registerFactory(cc_factory* factory);
    void clearMap();
    
}

#endif // CCPORTAL_H
