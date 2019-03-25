#ifndef CC_CONFIGURATION_HELPER_H
#define CC_CONFIGURATION_HELPER_H

#include <string>
#include <vector>
#include <sstream>

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
        
        std::vector<Number> ret;
        
        while(!(iss>>std::ws).eof())
        {
            Number value;
            iss>>value;
            ret.push_back(value);
        }
        
        return ret;
    }
}

#endif // CC_CONFIGURATION_HELPER_H
