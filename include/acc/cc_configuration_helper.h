#ifndef CC_CONFIGURATION_HELPER_H
#define CC_CONFIGURATION_HELPER_H

#include <string>
#include <vector>
#include <sstream>


//TEST
#include <iostream>

namespace cc
{
    
    bool getSetting(std::string configuration, const std::string& settingName, std::string& settingContents, const std::string& marker = "*");
    bool isNumber(const std::string& s);
    
    std::string getFirstWord(const std::string& configuraton);
    
    template<typename Number>
    Number getNumber(const std::string& word)
    {
        std::istringstream iss;
        iss.str(word);
        
        Number ret;
        iss>>ret;
        
        return ret;
    }
    
    template<typename Number>
    std::vector<Number> getVector(const std::string& configuration)
    {
        std::istringstream iss;
        iss.str(configuration);
        iss.clear();
        
        std::vector<Number> ret;
        Number value;
        
        while(iss>>value)
        {
            ret.push_back(value);
        }
        
        return ret;
    }
}

#endif // CC_CONFIGURATION_HELPER_H
