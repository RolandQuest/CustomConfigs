#ifndef CC_LOADER_H
#define CC_LOADER_H

#include <string>
#include <map>
#include <set>

namespace cc
{
    class cc_factory;
    class cc_component;
    typedef std::map<std::string, cc_component*> ComponentMap;
    
    class cc_loader
    {
        public:
            
            virtual ~cc_loader() = default;
            virtual bool Load(const std::string& configFile, ComponentMap& theMap, const std::set<cc_factory*>& availableFactories) = 0;
            
    };
}


#endif // CC_LOADER_H
