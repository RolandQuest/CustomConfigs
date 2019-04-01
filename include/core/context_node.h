#ifndef CONTEXT_NODE_H
#define CONTEXT_NODE_H

#include <vector>
#include <string>
#include <map>

#include "core/config_string.h"

namespace cc
{
    class context_node
    {
        public:
            
            context_node(context_node* parent = nullptr, size_t lineNumber = 0, const std::streampos& pos = 0);
            virtual ~context_node();
            
            bool IsRoot();
            void ReplaceName(const std::string& name, const std::string& expandedName);
            size_t LineCount();
            
            config_string _NodeContents;
            size_t _ReferenceLineNumber;
            std::streampos _ReferencePos;
            
            context_node* _Parent;
            std::map<std::string, context_node*> _Children;
            
    };
}

#endif // CONTEXT_NODE_H
