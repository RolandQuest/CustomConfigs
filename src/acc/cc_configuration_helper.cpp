#include "acc/cc_configuration_helper.h"

#include <algorithm>

//TODO: Need to implement input type (string/double/int/etc.) to prevent program stalling.

namespace cc
{
    size_t FindSettingStart(std::string configuration, const std::string& settingName, const std::string& marker)
    {
        size_t pos = configuration.find(marker, 0);
        while(pos != std::string::npos)
        {
            std::string subStringToLookAt = configuration.substr(pos + marker.size(), std::string::npos);
            std::istringstream iss(subStringToLookAt);
            
            std::string nextSetting;
            iss>>nextSetting;
            
            if(nextSetting == settingName)
            {
                return pos + iss.tellg();
            }
            
            pos = configuration.find(marker, pos + iss.tellg());
        }
        
        return pos;
    }
    
    bool getSetting(std::string configuration, const std::string& settingName, std::string& settingContents, const std::string& marker)
    {
        settingContents = "";
        size_t startPos = FindSettingStart(configuration, settingName, marker);
        
        if(startPos == std::string::npos)
        {
            return false;
        }
        
        size_t endPos = configuration.find(marker, startPos + 1);
        
        settingContents = configuration.substr(startPos + 1, endPos - startPos - 1);
        return true;
    }
    
    bool isNumber(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
    }
    
    std::string getFirstWord(const std::string& configuration)
    {
        std::istringstream iss;
        iss.str(configuration);
        
        std::string ret;
        iss>>ret;
        
        return ret;
    }
    
}


