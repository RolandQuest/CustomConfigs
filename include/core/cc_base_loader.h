#ifndef CC_BASE_LOADER_H
#define CC_BASE_LOADER_H

#include <string>
#include <vector>

#include "core/config_string.h"

namespace cc
{
    class cc_base_loader
    {
        public:
            
            cc_base_loader();
            virtual ~cc_base_loader();
            
        protected:
            
            //TODO: Make public...
            bool LoadFile(const std::string fileName);
            size_t LineCount();
            
            const std::string _LineCommentBegin = "//";
            const std::string _BlockCommentBegin = "/*";
            const std::string _BlockCommentEnd = "*/";
            
        protected:
            
            config_string _FileContents;
            std::string _FileName;
            
            void DestroyBlockComments(std::vector<std::string>& contents);
            void DestroyLineComments(std::vector<std::string>& contents);
            
    };

}

#endif // CC_BASE_LOADER_H
