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
    
    //Member variables
    extern ConfigurationMap _ConfigMap;
    extern ComponentMap _CompMap;
    extern cc_loader* _Loader;
    extern std::vector<cc_factory*> _FactoryVector;
    
    
    //Public functions
    bool load(const std::string& configFile);
    cc_loader* setLoader(cc_loader* loader);
    cc_factory* registerFactory(cc_factory* factory);
    void clearMap();
    
    
    //Template functions
    template<typename Comp>
    Comp* getComponentPointer(const std::string& name)
    {
        cc_component* orig = _CompMap[name];
        Comp* ret = dynamic_cast<Comp*>(orig);
        return ret;
    }
    
    template<typename Comp>
    Comp& getComponent(const std::string& name)
    {
        Comp* ret = getComponentPointer<Comp>(name);
        return *ret;
    }
}

#endif // CCPORTAL_H
