#ifndef CC_FACTORY_H
#define CC_FACTORY_H

#include <set>
#include <string>

namespace cc
{
    class cc_component;
    
    class cc_factory
    {
        public:
            
            virtual ~cc_factory() = default;
            
            virtual std::set<std::string> GetAvailableTypes() const = 0;
            virtual bool ContainsType(std::string type) const = 0;
            virtual cc_component* CreateComponent(const std::string& type, const std::string& name, const std::string& config) const = 0;
            
    };

}

#endif // CC_FACTORY_H
