#ifndef CC_DISTRIBUTION_CONFIG_H
#define CC_DISTRIBUTION_CONFIG_H

#include <string>
#include <vector>

#include "cc/cc_component_configuration.h"

namespace cc
{
    class cc_component;
    
    //TODO: Potentially make template class.
    class cc_distribution_config : public cc_component_configuration
    {
        public:
            
            cc_distribution_config(const std::string& name, const std::string& rawData);
            virtual ~cc_distribution_config();
            
            cc_component* Instantiate() override;
            bool Validate() override;
            std::vector<std::string> GetReferenceNames() override;
            
            //TODO: Potentially use getters/setters?
            std::string cc_mt19937_Comp;
            std::vector<double> Weights;
    };

}

#endif // CC_DISTRIBUTION_CONFIG_H
