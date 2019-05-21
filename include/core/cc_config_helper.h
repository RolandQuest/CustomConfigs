#ifndef CC_CONFIG_HELPER_H
#define CC_CONFIG_HELPER_H

#include <string>
#include <vector>
#include <sstream>

namespace cc
{
    
    bool GetSetting(const std::string& configuration, const std::string& settingName, std::string& settingContents, const std::string&  marker = "*");
    size_t FindSettingStart(const std::string& configuration, const std::string& settingName, const std::string&  marker);
    
    std::string GetFirstWord(const std::string& content);
    std::vector<std::string> GetWordVector(const std::string& content);
    std::vector< std::vector<std::string> > GetWordVector2d(const std::string& content);
    bool IsNumber(const std::string& s);
    bool IsDoubleType(const std::string& s);
    bool IsIntType(const std::string& s);
    
    std::string Trim(const std::string& str);
    std::string LeftTrim(const std::string& str);
    std::string RightTrim(const std::string& str);
    
    template<class T>
    T ConvertWord(const std::string& content)
    {
        std::istringstream stream;
        stream.str(content);
        stream.clear();
        
        T value;
        stream>>value;
        return value;
    }
    
    template<class T>
    std::vector<T> ConvertVector(const std::vector<std::string>& content)
    {
        std::istringstream stream;
        std::vector<T> ret;
        
        for(size_t i = 0; i < content.size(); i++)
        {
            stream.str(content[i]);
            stream.clear();
            
            T value;
            stream>>value;
            
            ret.push_back(value);
        }
        
        return ret;
    }
    
}

#endif // CC_CONFIG_HELPER_H
