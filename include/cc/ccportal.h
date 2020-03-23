#ifndef CCPORTAL_H
#define CCPORTAL_H

#include <map>
#include <string>
#include <set>
#include <ostream>

#include "cc/cclog.h"
#include "cc/cc_factory.h"
#include "cc/cc_loader.h"
#include "cc/cc_component.h"

namespace cc
{

    //Member variables
    extern cc_ComponentMap _CompMap;
    extern cc_loader* _Loader;
    extern cc_FactorySet _FactorySet;
    
    //Public functions
    bool load(const std::string& configFile);
    bool initialize();
    void serialize(std::ostream& stream);
    cc_loader* setLoader(cc_loader* loader);
    cc_factory* registerFactory(cc_factory* factory);
    void clearComponentMap();
    void setCCLogFileBuf(std::filebuf* fileBuf);
    bool checkForComponent(const std::string name);
    
    
    //Template functions
    
    template<typename Comp>
    bool checkComponentType(const std::string& name)
    {
        if(!checkForComponent(name))
        {
            return false;
        }
        
        return dynamic_cast<Comp*>(_CompMap[name]);
    }
    
    template<typename Comp>
    bool getComponentCheck(const std::string name)
    {
        if(checkForComponent(name))
        {
            if(checkComponentType<Comp>(name))
            {
                return true;
            }
            else
            {
                Log("cc::getComponentCheck failure: Type check did not succeed on component '", name, "'.");
            }
        }
        else
        {
            Log("cc::getComponentCheck failure: Component of name '", name, "' did not exist in map.");
        }
        return false;
    }
    
    template<typename Comp>
    Comp* getComponentPointer(const std::string& name)
    {
        if(!getComponentCheck<Comp>(name))
        {
            return nullptr;
        }
        
        cc_component* orig = _CompMap[name];
        Comp* ret = dynamic_cast<Comp*>(orig);
        return ret;
    }
    
    template<typename Comp>
    Comp& getComponent(const std::string& name)
    {
        getComponentCheck<Comp>(name);
        Comp* ret = getComponentPointer<Comp>(name);
        return *ret;
    }
    
    
    
    
}

#endif // CCPORTAL_H





