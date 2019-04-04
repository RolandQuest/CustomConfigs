#include "core/cc_base_loader.h"

#include <fstream>

namespace cc
{
    
    cc_base_loader::cc_base_loader()
    {
        //ctor
    }

    cc_base_loader::~cc_base_loader()
    {
        //dtor
    }
    
    bool cc_base_loader::LoadFile(const std::string fileName)
    {
        _FileName = fileName;
        
        std::ifstream stream(fileName);
        if(!stream.is_open())
        {
            return false;
        }
        
        std::vector<std::string> tempContents;
        std::string lineContent;
        while(getline(stream, lineContent))
        {
            tempContents.push_back(lineContent);
        }
        
        stream.close();
        DestroyBlockComments(tempContents);
        DestroyLineComments(tempContents);
        _FileContents = config_string(tempContents);
        return true;
    }
    
    size_t cc_base_loader::LineCount()
    {
        return _FileContents.LineCount();
    }
    
    void cc_base_loader::DestroyBlockComments(std::vector<std::string>& contents)
    {
        bool isCommenting = false;
        
        for(size_t lineIndex = 0; lineIndex < contents.size(); lineIndex++)
        {
            std::string& line = contents[lineIndex];
            
            if(isCommenting)
            {
                size_t stopPos = line.find(_BlockCommentEnd);
                if(stopPos != std::string::npos)
                {
                    line.erase(0, stopPos + _BlockCommentEnd.size());
                    
                    //So the loop will reconsider this line.
                    lineIndex--;
                    isCommenting = false;
                }
            }
            else
            {
                size_t pos = line.find(_BlockCommentBegin);
                if(pos != std::string::npos)
                {
                    isCommenting = true;
                    
                    //Checks if a closure on the same line.
                    size_t stopPos = line.find(_BlockCommentEnd);
                    if(stopPos != std::string::npos)
                    {
                        line.erase(pos, stopPos - pos + _BlockCommentEnd.size() - 1);
                        
                        //So the loop will reconsider this line.
                        lineIndex--;
                        isCommenting = false;
                    }
                }
            }
            
            
        }
    }
    
    void cc_base_loader::DestroyLineComments(std::vector<std::string>& contents)
    {
        for(std::string& line : contents)
        {
            size_t pos = line.find(_LineCommentBegin);
            if(pos != std::string::npos)
            {
                line.erase(begin(line) + pos, end(line));
            }
        }
    }
    
}
