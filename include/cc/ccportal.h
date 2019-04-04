#ifndef CCPORTAL_H
#define CCPORTAL_H

#include <map>
#include <string>
#include <set>

namespace cc
{
    class cc_factory;
    class cc_loader;
    class cc_component;
    class cc_configuration_mapper;
    typedef std::map<std::string, cc_component*> ComponentMap;
    
    //Member variables
    extern ComponentMap _CompMap;
    extern cc_loader* _Loader;
    extern cc_configuration_mapper* _ConfigMapper;
    extern std::set<cc_factory*> _FactorySet;
    
    
    //Public functions
    bool load(const std::string& configFile);
    cc_loader* setLoader(cc_loader* loader);
    cc_configuration_mapper* setConfigMapper(cc_configuration_mapper* mapper);
    cc_factory* registerFactory(cc_factory* factory);
    void clearComponentMap();
    void setCCLogFileBuf(std::filebuf* fileBuf);
    
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
