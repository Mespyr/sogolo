#include "node.hpp"

namespace Sogolo
{
    Node::Node(ParserNodeType t, std::string& l, unsigned int ln, std::string& v)
    {
        type = t;
        line = l;
        line_number = ln;
        value = v;
    }
    
    Node::~Node()
    {}


    void Node::set(ParserNodeType t, std::string& l, unsigned int ln, std::string& v)
    {
        type = t;
        line = l;
        line_number = ln;
        value = v;
    }

} // namespace Sogolo
