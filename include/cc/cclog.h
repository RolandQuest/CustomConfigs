#ifndef CCLOG_H
#define CCLOG_H

#include <iostream>
#include <fstream>

namespace cc
{
    
    extern std::filebuf* _cc_log_TargetFileBuffer;
    extern std::streambuf* _cc_log_OriginalClogBuffer;
    
    template<typename First>
    void LogIterator(const First& msg)
    {
        std::clog<<msg<<std::endl;
    }

    template<typename First, typename ...Rest>
    void LogIterator(const First& msg, const Rest& ...params)
    {
        std::clog<<msg;
        LogIterator(params...);
    }
    
    template<typename ...Rest>
    void Log(Rest... params)
    {
        if(_cc_log_TargetFileBuffer != nullptr && _cc_log_TargetFileBuffer->is_open())
        {
            std::clog.rdbuf(_cc_log_TargetFileBuffer);
        }
        
        LogIterator(params...);
        std::clog.rdbuf(_cc_log_OriginalClogBuffer);
    }
    
}


#endif // CCLOG_H
