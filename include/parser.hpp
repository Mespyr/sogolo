#ifndef FENNEC_PARSER_H
#define FENNEC_PARSER_H

#include "token.hpp"
#include "error.hpp"

namespace Parser {
    enum ASTNodeType {
        AST_BLOCK,
        AST_LINE,
        AST_EXPRESSION,
        AST_ARGMAP,
        AST_FUNCTION_CALL,
        AST_ATOM
    };

    enum AtomType {
        OBJ_STRING,
        OBJ_NUMBER,
        OBJ_CHAR,
        AST_SYMBOL
    };
    std::string get_type(AtomType tp);


    // Base type. Can either by Block, Expression, ArgMap, Line, or Atom.
    class Node {
    public:
        ASTNodeType type;
        std::vector<Node> nodes;

        // Location of node in file
        std::string line;
        unsigned int line_number;

        std::string value;
        AtomType atom_type;
    };

    // Functions
    AtomType generate_atom_type(std::string str);
    bool is_number(const std::string& s);
    std::string get_type(AtomType tp);





    // Parser
    class Parser {
    public:
        Token::TokenStream stream;
        Node ast;

        // Errors
        bool error_found = false;
        error_type ErrorType;
        EOF_ERROR eof_error;
        PARSING_ERROR parsing_error;
        PARSING_ERROR_NO_TOKEN no_token_parsing_error;

        std::string get_error();

        // Functions
        void parse();
        Node parse_next_node();

        Node build_Block_from_vector(std::vector<Node> vec, std::string line, unsigned int line_number);
        Node build_Expression_from_vector(std::vector<Node> vec, std::string line, unsigned int line_number);
        Node build_ArgMap_from_vector(std::vector<Node> vec, std::string line, unsigned int line_number);


        // Debugging
        void debug_print(Node node, std::string indent = "");
        void debug_print_vector(Node node, std::string indent);
    };


} // namespace Parser

#endif