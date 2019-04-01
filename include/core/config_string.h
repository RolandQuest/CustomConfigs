#ifndef CONFIG_STRING_H
#define CONFIG_STRING_H

#include <vector>
#include <string>
#include <ostream>

namespace cc
{
    class config_string
    {
        
        public:
            
            config_string();
            config_string(const std::string& str);
            config_string(const config_string& other);
            config_string(const config_string&& other);
            config_string(const std::vector<std::string>& strVec);
            virtual ~config_string();
            inline void CalculateLineCount();
            
            size_t LineCount() const;
            size_t Size() const;
            void Clear();
            bool IsEmpty() const;
            void AppendLine(const std::string& str);
            const char At(size_t pos) const;
            bool GetLineAt(std::string& container, size_t lineNumber, std::streampos startPos = 0) const;
            bool Replace(const std::string& toBeReplaced, const std::string& newSubString);
            size_t Find(const std::string& str, size_t pos = 0) const;
            size_t Find(char str, size_t pos = 0) const;
            config_string SubStr(size_t pos, size_t len = std::string::npos) const;
            std::string SubStrTrue(size_t pos, size_t len = std::string::npos) const;
            std::string GetDataCopy() const;
            
            config_string& operator=(const config_string& other);
            config_string& operator=(const config_string&& other);
            config_string& operator=(const std::string& other);
            config_string& operator=(const std::string&& other);
            config_string& operator+=(const std::string& str);
            const char operator[](size_t index);
            friend std::ostream& operator<<(std::ostream& os, const config_string& cs);
            
        private:
            
            size_t _LineCount = 0;
            std::string _Data;
            
    };
}

#endif // CONFIG_STRING_H
