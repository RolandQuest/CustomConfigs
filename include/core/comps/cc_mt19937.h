#ifndef CC_MT19937_H
#define CC_MT19937_H

#include <vector>
#include <string>
#include <map>
#include <random>

#include "cc/cc_component.h"

namespace cc
{
    class cc_component_configuration;
    
    class cc_mt19937 : public cc_component, public std::mt19937
    {
        public:
            
            cc_mt19937(cc_component_configuration* config, const size_t& rawData);
            virtual ~cc_mt19937();

            bool Link(std::map<std::string, cc_component*>& availableComponents) override;
            
    };

}

#endif // CC_MT19937_H
