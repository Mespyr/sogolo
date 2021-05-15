#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

namespace Sogolo
{
    enum ParserNodeType {
        NODE_EXPRESSION,
        NODE_BLOCK,
        NODE_LINE,
        NODE_ARGMAP,
        NODE_FUNCTION_CALL,
        NODE_ATOM
    };

    enum ParserAtomType {
        OBJ_STRING,
        OBJ_NUMBER,
        OBJ_CHAR,
        NODE_SYMBOL
    };

    class Node
    {
    public:
        ParserNodeType type;
        std::vector<Node> nodes;

        // Location of node in file
        std::string line;
        unsigned int line_number;

        std::string value;
        ParserAtomType atom_type;


        Node(ParserNodeType t, std::string& l, unsigned int ln, std::string& v);
        // For ast
        Node() {}

        ~Node();

        void set(ParserNodeType t, std::string& l, unsigned int ln, std::string& v);
    };
    


} // namespace Sogolo


#endif