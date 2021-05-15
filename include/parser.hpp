#ifndef PARSER_H
#define PARSER_H

#include "token.hpp"
#include "errors.hpp"
#include "node.hpp"

namespace Sogolo
{
    class Parser
    {
    public:
        TokenStream stream;
        Node ast;

        // Errors
        bool error_found = false;
        Error error;

        Parser(TokenStream& s);
        ~Parser();


        Node build_Block_from_vector(std::vector<Node> vec, std::string line, unsigned int line_number);
        Node build_Expression_from_vector(std::vector<Node> vec, std::string line, unsigned int line_number);
        Node build_ArgMap_from_vector(std::vector<Node> vec, std::string line, unsigned int line_number);


        void parse();
        Node parse_next_node();

        // Debugging
        void debug_print(Node node, std::string indent = "");
        void debug_print_vector(Node node, std::string indent);
    };
    
    
} // namespace Sogolo



#endif