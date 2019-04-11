#ifndef CC_CONFIGURATION_MAPPER_H
#define CC_CONFIGURATION_MAPPER_H

#include <string>
#include <vector>
#include <sstream>

namespace cc
{
    class cc_configuration_mapper
    {
        public:
            
            virtual bool GetSetting(const std::string& configuration, const std::string& settingName, std::string& settingContents) = 0;
            virtual std::string GetWord(const std::string& content) = 0;
            virtual std::vector<std::string> GetWordVector(const std::string& content) = 0;
            virtual std::vector< std::vector<std::string> > GetWordVectorVector(const std::string& content) = 0;
            virtual bool IsNumber(const std::string& IsNumber) = 0;
            virtual bool IsDoubleType(const std::string& IsNumber) = 0;
            virtual bool IsIntType(const std::string& IsNumber) = 0;
            
            template<class T>
            std::vector<T> ConvertVector(const std::vector<std::string>& content);
            
            template<class T>
            T ConvertWord(const std::string& content);
            
    };
    
    template<class T>
    T cc_configuration_mapper::ConvertWord(const std::string& content)
    {
        std::istringstream stream;
        stream.str(content);
        stream.clear();
        
        T value;
        stream>>value;
        return value;
    }
    
    template<class T>
    std::vector<T> cc_configuration_mapper::ConvertVector(const std::vector<std::string>& content)
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

#endif // CC_CONFIGURATION_MAPPER_H
