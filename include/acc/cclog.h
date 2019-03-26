#ifndef CCLOG_H
#define CCLOG_H

#include <ostream>

namespace cc
{
    
    void setLogStream(std::ostream& stream);
    
    void useBufferOfStream(const std::ofstream* stream);
}


#endif // CCLOG_H
