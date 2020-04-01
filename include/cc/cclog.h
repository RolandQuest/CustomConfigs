#ifndef CCLOG_H
#define CCLOG_H

#include <iostream>
#include <fstream>

namespace cc
{
    //! The buffer the log will send messages via clog to.
    extern std::filebuf* _cc_log_TargetFileBuffer;

    //! The original clog buffer.
    extern std::streambuf* _cc_log_OriginalClogBuffer;
    
    //! Part 3/3 - Writes a message to clog and endlines.
    template<typename First>
    void LogIterator(const First& msg)
    {
        std::clog<<msg<<std::endl;
    }

    //! Part 2/3 - Writes a message to clog and endlines.
    template<typename First, typename ...Rest>
    void LogIterator(const First& msg, const Rest& ...params)
    {
        std::clog<<msg;
        LogIterator(params...);
    }
    
    //! Part 1/3 - Writes a message to clog and endlines.
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
