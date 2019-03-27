#ifndef CCLOG_H
#define CCLOG_H

#include <iostream>
#include <fstream>

namespace cc
{
    
    extern std::filebuf* _TargetFileBuffer;
    extern std::streambuf* _OriginalClogBuffer;
    
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
        
        
        
        
        if(_TargetFileBuffer->is_open())
        {
            std::clog.rdbuf(_TargetFileBuffer);
        }
        
        //std::clog.rdbuf(_TargetBuffer);
        LogIterator(params...);
        std::clog.rdbuf(_OriginalClogBuffer);
    }
    
}


#endif // CCLOG_H
