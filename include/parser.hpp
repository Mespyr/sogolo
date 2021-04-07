#ifndef EDULO_PARSER_H
#define EDULO_PARSER_H

#include "token.hpp"
#include "error.hpp"

namespace Parser
{
    enum ASTNodeType
    {
        BLOCK,
        EXPRESSION,
        ARGMAP,
        LINE,
        ATOM
    };


    // Atom. Holds token.
    class Atom
    {
    public:
        Token::Token token;
    };


    // Base type. Can either by Block, Expression, ArgMap, or Atom.
    class Node
    {
    public:
        ASTNodeType type;
        std::vector<std::vector<Node>> block;
        std::vector<Node> expr;
        std::vector<Node> argmap;
        Atom atom;
    };



    // Parser stuff
    class Parser
    {
    public:
        Token::TokenStream stream;
        Node ast;

        bool error_found = false;
        error_type ErrorType;
        EOF_ERROR eof_error;
        PARSING_ERROR parsing_error;

        // Functions
        void parse();
        Node parse_next_node();

        Node build_Block_from_vector(std::vector<Node> vec);
        Node build_Expression_from_vector(std::vector<Node> vec);
        Node build_ArgMap_from_vector(std::vector<Node> vec);


        // Debugging
        void debug_print(Node node, std::string indent = "");
        void print_line(std::vector<Node> line, std::string indent = "");
    };


} // namespace Parser


#endif