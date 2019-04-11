#include "core/cc_config_helper.h"

#include <algorithm>

namespace cc
{
    
    bool GetSetting(const std::string& configuration, const std::string& settingName, std::string& settingContents, const std::string& marker)
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
    
    size_t FindSettingStart(const std::string& configuration, const std::string& settingName, const std::string&  marker)
    {
        size_t pos = configuration.find(marker, 0);
        while(pos != std::string::npos)
        {
            std::string subStringToLookAt = configuration.substr(pos + marker.size(), std::string::npos);
            std::istringstream iss(subStringToLookAt);
            
            std::string nextSetting;
            iss>>nextSetting;
            
            std::transform(std::begin(nextSetting),std::end(nextSetting),std::begin(nextSetting),::tolower);
            
            if(nextSetting == settingName)
            {
                return pos + iss.tellg();
            }
            
            pos = configuration.find(marker, pos + iss.tellg());
        }
        
        return pos;
    }
    
    std::string GetFirstWord(const std::string& content)
    {
        std::istringstream stream;
        stream.str(content);
        stream.clear();
        
        std::string ret;
        stream>>ret;
        
        return ret;
    }
    
    std::vector<std::string> GetWordVector(const std::string& content)
    {
        std::vector<std::string> ret;
        
        std::istringstream stream;
        stream.str(content);
        stream.clear();
        
        std::string word;
        while(stream>>word)
        {
            ret.push_back(word);
        }
        
        return ret;
    }
    
    bool IsNumber(const std::string& s)
    {
        //TODO: Travis has better way.
        return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
    }
    
    bool IsDoubleType(const std::string& s)
    {
        //TODO: Fill this out please.
        return false;
    }
    
    bool IsIntType(const std::string& s)
    {
        //TODO: Fill this out please.
        return false;
    }
    
    std::string Trim(const std::string& s)
    {
        std::string ret;
        ret = LeftTrim(s);
        ret = RightTrim(ret);
        return ret;
    }
    
    std::string LeftTrim(const std::string& s)
    {
        std::string ret = s;
        ret.erase(std::begin(ret), std::find_if(std::begin(ret), std::end(ret), [](int ch){ return !std::isspace(ch); }));
        return ret;
    }
    
    std::string RightTrim(const std::string& s)
    {
        std::string ret;
        ret.erase(std::find_if(std::rbegin(ret), std::rend(ret), [](int ch){ return !std::isspace(ch); }).base(), std::end(ret));
        return ret;
    }


    
    
    
    
    
    /*
    ARCHIVES
    ----------
    std::vector< std::vector<std::string> > GetWordVectorVector(const std::string& content)
    {
        std::vector< std::vector<std::string> > ret;
        
        std::istringstream fullStream;
        fullStream.str(content);
        fullStream.clear();
        
        std::string lineContents;
        while(std::getline(fullStream, lineContents))
        {
            std::istringstream lineStream;
            lineStream.str(lineContents);
            lineStream.clear();
            
            std::vector<std::string> layer;
            
            std::string word;
            while(lineStream>>word)
            {
                layer.push_back(word);
            }
            
            if(layer.size() > 0)
            {
                ret.push_back(layer);
            }
        }
        
        return ret;
    }
    */

}
