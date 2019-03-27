#include "acc/cclog.h"

namespace cc
{

    //TODO: This requires that the clog streambuf hasn't been altered already.
    std::filebuf* _TargetFileBuffer;
    std::streambuf* _OriginalClogBuffer;
    
}
