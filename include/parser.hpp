#ifndef EDULO_PARSER_H
#define EDULO_PARSER_H

#include "token.hpp"

namespace Parser
{
    enum ASTNodeType
    {
        BLOCK,
        EXPRESSION,
        ARGMAP,
        LINE
    };


    // Base type. Can either by Block, Expression, or ArgMap.
    class Node
    {
    public:
        ASTNodeType type;
        Block block;
        Expression expr;
        ArgMap argmap;
    };


    // Contains lines of code. Surrounded by '{' and '}'.
    class Block
    {
    public:
        std::vector<Line> lines;
    };

    class Line
    {
    public:
        std::vector<Node> line;
    };


    // Expressions. Surrounded by '(' and ')'
    class Expression
    {
    public:
        std::vector<Node> expr;
    };


    // Different arguments. Surrounded by '[' and ']'
    class ArgMap
    {
    public:
        std::vector<Node> argv;
    };


    // Parser stuff
    class Parser
    {
    public:
        Token::TokenStream stream;
        Block ast;

        bool error_found = false;

        void parse();
        Node parse_next_node();

        void debug_print();
    };
} // namespace Parser


#endif