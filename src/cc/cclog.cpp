#include "cc/cclog.h"

namespace cc
{

    //TODO: This requires that the clog streambuf hasn't been altered already.
    std::filebuf* _cc_log_TargetFileBuffer = nullptr;
    std::streambuf* _cc_log_OriginalClogBuffer = std::clog.rdbuf();
    
}
