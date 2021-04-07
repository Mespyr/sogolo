#include "../include/parser.hpp"


Parser::Node Parser::Parser::parse_next_node()
{
    Token::Token token = stream.next();
    if (stream.eof)
    {
        
    }
    else
    {
        
    }
}


void Parser::Parser::parse()
{
    std::vector<Node> non_sorted_ast;
    while (!stream.eof)
    {
        Node node = parse_next_node();
        non_sorted_ast.push_back(node);
    }
}