#include "core/config_string.h"

#include <algorithm>
#include <sstream>

namespace cc
{

    config_string::config_string()
    {
        //ctor
    }

    config_string::config_string(const std::string& str)
    {
        _Data = str;
        CalculateLineCount();
    }
    config_string::config_string(const std::vector<std::string>& strVec)
    {
        for(size_t i = 0; i < strVec.size(); i++)
        {
            _Data.insert(std::end(_Data), std::begin(strVec[i]), std::end(strVec[i]));
            _Data.push_back('\n');
        }
        
        CalculateLineCount();
    }
    config_string::config_string(const config_string& other)
    {
        _Data = other._Data;
        _LineCount = other._LineCount;
    }
    config_string::config_string(const config_string&& other)
    {
        _Data = other._Data;
        _LineCount = other._LineCount;
    }
    config_string::~config_string()
    {
        //dtor
    }
    
    inline void config_string::CalculateLineCount()
    {
        _LineCount = std::count(std::begin(_Data), std::end(_Data), '\n') + 1;
    }
    
    
    
    
    
    size_t config_string::LineCount() const
    {
        return _LineCount;
    }
    size_t config_string::Size() const
    {
        return _Data.size();
    }
    void config_string::Clear()
    {
        _Data.clear();
        _LineCount = 1;
    }
    bool config_string::IsEmpty() const
    {
        return _Data.empty();
    }
    void config_string::AppendLine(const std::string& str)
    {
        _Data.push_back('\n');
        _Data.insert(std::end(_Data), std::begin(str), std::end(str));
        CalculateLineCount();
    }
    const char config_string::At(size_t pos) const
    {
        return _Data.at(pos);
    }
    bool config_string::GetLineAt(std::string& container, size_t lineNumber, std::streampos startPos) const
    {
        size_t currentLine = 0;
        
        std::istringstream stream;
        stream.str(_Data);
        stream.clear();
        
        while(std::getline(stream, container))
        {
            if(currentLine == lineNumber)
            {
                container = container.substr(startPos, std::string::npos);
                return true;
            }
            currentLine++;
        }
        
        container = "";
        return false;
    }
    bool config_string::Replace(const std::string& toBeReplaced, const std::string& newSubString)
    {
        size_t pos = _Data.find(toBeReplaced);
        if(pos != std::string::npos)
        {
            _Data.erase(pos, toBeReplaced.size());
            _Data.insert(pos, newSubString);
            return true;
        }
        return false;
    }
    size_t config_string::Find(const std::string& str, size_t pos) const
    {
        return _Data.find(str, pos);
    }
    size_t config_string::Find(char str, size_t pos) const
    {
        return _Data.find(str, pos);
    }
    config_string config_string::SubStr(size_t pos, size_t len) const
    {
        config_string ret = _Data.substr(pos, len);
        return ret;
    }
    std::string config_string::SubStrTrue(size_t pos, size_t len) const
    {
        return _Data.substr(pos, len);
    }
    std::string config_string::GetDataCopy() const
    {
        std::string ret = _Data;
        return ret;
    }
    
    
    
    
    
    config_string& config_string::operator=(const config_string& other)
    {
        if(this != &other)
        {
            _Data = other._Data;
            _LineCount = other._LineCount;
        }
        return *this;
    }
    config_string& config_string::operator=(const config_string&& other)
    {
        if(this != &other)
        {
            _Data = other._Data;
            _LineCount = other._LineCount;
        }
        return *this;
    }
    config_string& config_string::operator=(const std::string& other)
    {
        _Data = other;
        CalculateLineCount();
        return *this;
    }
    config_string& config_string::operator=(const std::string&& other)
    {
        _Data = other;
        CalculateLineCount();
        return *this;
    }
    config_string& config_string::operator+=(const std::string& str)
    {
        _Data += str;
        CalculateLineCount();
        return *this;
    }
    const char config_string::operator[](size_t index)
    {
        return _Data.at(index);
    }
    std::ostream& operator<<(std::ostream& os, const config_string& cs)
    {
        os<<cs.GetDataCopy();
        return os;
    }

    
    
    

    
}
