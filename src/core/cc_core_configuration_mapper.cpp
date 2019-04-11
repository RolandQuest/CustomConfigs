#include "core/cc_core_configuration_mapper.h"

#include <algorithm>

namespace cc
{
    cc_core_configuration_mapper::cc_core_configuration_mapper()
    {
        //ctor
    }

    cc_core_configuration_mapper::cc_core_configuration_mapper(const std::string& marker)
    {
        _Marker = marker;
    }
    
    cc_core_configuration_mapper::~cc_core_configuration_mapper()
    {
        //dtor
    }

    bool cc_core_configuration_mapper::GetSetting(const std::string& configuration, const std::string& settingName, std::string& settingContents)
    {
        settingContents = "";
        size_t startPos = FindSettingStart(configuration, settingName);
        
        if(startPos == std::string::npos)
        {
            return false;
        }
        
        size_t endPos = configuration.find(_Marker, startPos + 1);
        
        settingContents = configuration.substr(startPos + 1, endPos - startPos - 1);
        return true;
    }
    
    size_t cc_core_configuration_mapper::FindSettingStart(const std::string& configuration, const std::string& settingName)
    {
        size_t pos = configuration.find(_Marker, 0);
        while(pos != std::string::npos)
        {
            std::string subStringToLookAt = configuration.substr(pos + _Marker.size(), std::string::npos);
            std::istringstream iss(subStringToLookAt);
            
            std::string nextSetting;
            iss>>nextSetting;
            
            std::transform(std::begin(nextSetting),std::end(nextSetting),std::begin(nextSetting),::tolower);
            
            if(nextSetting == settingName)
            {
                return pos + iss.tellg();
            }
            
            pos = configuration.find(_Marker, pos + iss.tellg());
        }
        
        return pos;
    }
    
    std::string cc_core_configuration_mapper::GetWord(const std::string& content)
    {
        std::string ret = content;
        Trim(ret);
        return ret;
    }
    
    std::vector<std::string> cc_core_configuration_mapper::GetWordVector(const std::string& content)
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
    
    std::vector< std::vector<std::string> > cc_core_configuration_mapper::GetWordVectorVector(const std::string& content)
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
    
    bool cc_core_configuration_mapper::IsNumber(const std::string& s)
    {
        //TODO: Travis has better way.
        return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
    }
    
    bool cc_core_configuration_mapper::IsDoubleType(const std::string& s)
    {
        //TODO: Fill this out please.
        return false;
    }
    
    bool cc_core_configuration_mapper::IsIntType(const std::string& s)
    {
        //TODO: Fill this out please.
        return false;
    }
    
    inline void cc_core_configuration_mapper::Trim(std::string& s)
    {
        LeftTrim(s);
        RightTrim(s);
    }
    
    inline void cc_core_configuration_mapper::LeftTrim(std::string& s)
    {
        s.erase(std::begin(s), std::find_if(std::begin(s), std::end(s), [](int ch){ return !std::isspace(ch); }));
    }
    
    inline void cc_core_configuration_mapper::RightTrim(std::string& s)
    {
        s.erase(std::find_if(std::rbegin(s), std::rend(s), [](int ch){ return !std::isspace(ch); }).base(), std::end(s));
    }



}
