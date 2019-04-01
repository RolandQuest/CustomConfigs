#include "acc/cclog.h"

namespace cc
{

    //TODO: This requires that the clog streambuf hasn't been altered already.
    std::filebuf* _TargetFileBuffer = nullptr;
    std::streambuf* _OriginalClogBuffer = std::clog.rdbuf();
    
}
