#ifndef CC_BASE_LOADER_H
#define CC_BASE_LOADER_H

#include <string>
#include <fstream>
#include <sstream>

namespace cc
{
    class cc_base_loader
    {
        public:
            
            cc_base_loader();
            virtual ~cc_base_loader();
            
        protected:
                
                bool OpenFile();
                void CloseFile();
                bool NextLine();
                void DestroyLineComment();
                
                int _LineNumber;
                std::istringstream _LineBuffer;
                std::ifstream _InputStream;
                std::string _LineBeingRead;
                std::string _FileName;
                
                const std::string _LineCommentBegin = "//";
                
    };

}

#endif // CC_BASE_LOADER_H
