#include "acc/cclog.h"

#include <ostream>
#include <fstream>
#include <iostream>

namespace cc
{
    
    void useBufferOfStream(const std::ofstream* stream)
    {
        std::clog.rdbuf((*stream).rdbuf());
    }
    
    void setLogStream(std::ostream& stream)
    {
        
    }
}
