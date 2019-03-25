#include "acc/cc_base_loader.h"

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
    
    bool cc_base_loader::OpenFile()
    {
        _LineNumber = 0;
        _InputStream.open(_FileName, std::ifstream::in);
        
        return _InputStream.is_open();
    }
    void cc_base_loader::CloseFile()
    {
        _InputStream.close();
    }
    bool cc_base_loader::NextLine()
    {
        bool errorBit = (bool) getline(_InputStream, _LineBeingRead);
        
        _LineNumber++;
        DestroyLineComment();
        
        _LineBuffer.str(_LineBeingRead);
        _LineBuffer.clear();
        
        if(errorBit)
        {
            if((_LineBuffer>>std::ws).eof())
            {
                return NextLine();
            }
        }
        
        return errorBit;
    }
    void cc_base_loader::DestroyLineComment()
    {
        size_t pos = _LineBeingRead.find(_LineCommentBegin);
        if(pos != std::string::npos)
        {
            _LineBeingRead.erase(begin(_LineBeingRead) + pos, end(_LineBeingRead));
        }
    }
}
