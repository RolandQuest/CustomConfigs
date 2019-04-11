#ifndef CC_CORE_CONFIGURATION_MAPPER_H
#define CC_CORE_CONFIGURATION_MAPPER_H

#include <string>
#include <vector>

#include "cc/cc_configuration_mapper.h"
 
namespace cc
{
    class cc_core_configuration_mapper : public cc_configuration_mapper
    {
        public:
            
            cc_core_configuration_mapper();
            cc_core_configuration_mapper(const std::string& marker);
            virtual ~cc_core_configuration_mapper();

            bool GetSetting(const std::string& configuration, const std::string& settingName, std::string& settingContents) override;
            std::string GetWord(const std::string& content) override;
            std::vector<std::string> GetWordVector(const std::string& content) override;
            std::vector< std::vector<std::string> > GetWordVectorVector(const std::string& content) override;
            bool IsNumber(const std::string& s) override;
            bool IsDoubleType(const std::string& s) override;
            bool IsIntType(const std::string& s) override;
            
        private:
            
            size_t FindSettingStart(const std::string& configuration, const std::string& settingName);
            inline void LeftTrim(std::string& str);
            inline void RightTrim(std::string& str);
            inline void Trim(std::string& str);
            
            std::string _Marker = "*";
    };
    
}

#endif // CC_CORE_CONFIGURATION_MAPPER_H
