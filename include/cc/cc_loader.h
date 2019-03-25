#ifndef CC_LOADER_H
#define CC_LOADER_H

#include <string>
#include <map>
#include <vector>

namespace cc
{
    class cc_component_configuration;
    class cc_factory;
    typedef std::map<std::string, cc_component_configuration*> ConfigurationMap;
    
    class cc_loader
    {
        public:
            
            virtual ~cc_loader() = default;
            
            virtual bool Load(const std::string& configFile, ConfigurationMap& theMap, const std::vector<cc_factory*>& availableFactories) = 0;
            
    };
}


#endif // CC_LOADER_H
