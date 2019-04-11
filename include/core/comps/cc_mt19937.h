#ifndef CC_MT19937_H
#define CC_MT19937_H

#include <string>
#include <map>
#include <random>

#include "cc/cc_component.h"

namespace cc
{
    class cc_mt19937 : public cc_component, public std::mt19937
    {
        public:
            
            cc_mt19937(const std::string& name, const std::string& config);
            virtual ~cc_mt19937();

            bool Initialize(std::map<std::string, cc_component*>& availableComponents) override;
            size_t GetSeed();
            
        private:
            
            void ExtractSeed();
            
            size_t _Seed;
        
    };

}

#endif // CC_MT19937_H
