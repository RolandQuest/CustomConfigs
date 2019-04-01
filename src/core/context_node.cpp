#include "core/context_node.h"

namespace cc
{
    context_node::context_node(context_node* parent, size_t lineNumber, const std::streampos& pos)
    {
        _Parent = parent;
        _ReferenceLineNumber = lineNumber;
        _ReferencePos = pos;
    }
    
    context_node::~context_node()
    {
        //dtor
    }

    bool context_node::IsRoot()
    {
        return _Parent == nullptr;
    }
    
    void context_node::ReplaceName(const std::string& name, const std::string& expandedName)
    {
        _NodeContents.Replace(name, expandedName);
    }
    
    size_t context_node::LineCount()
    {
        return _NodeContents.LineCount();
    }
}
