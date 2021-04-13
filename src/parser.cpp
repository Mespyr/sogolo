#include "../include/parser.hpp"

// Errors ###########################################################
std::string Parser::EOF_ERROR::error()
{
    std::string error_msg = "EOF Error on line " + std::to_string(token.line_number) + ".\n";
    error_msg += "  " + token.line + "\n";
    error_msg += msg + "\n";
    return error_msg;
}

std::string Parser::PARSING_ERROR::error()
{
    std::string error_msg = "Parsing Error on line " + std::to_string(token.line_number) + ".\n";
    error_msg += token.line + "\n";
    error_msg += msg + "\n";
    return error_msg;
}

std::string Parser::Parser::get_error()
{
    if (ErrorType == EOF_)
    {
        return eof_error.error();
    }
    else
    {
        return parsing_error.error();
    }
}
// Parser ###########################################################


// build a Block node from vector generated by parser.
Parser::Node Parser::Parser::build_Block_from_vector(std::vector<Node> vec)
{
    Node node{AST_BLOCK};
    std::vector<Node> curline;
    for (int i = 0; i < vec.size(); i++)
    {
        Node curnode = vec.at(i);
        if (curnode.type == AST_ATOM)
        {
            if (curnode.atom.token.value == ";")
            {
                node.block.push_back(curline);
                curline.clear();
                continue;
            }
        }
        else if (curnode.type == AST_BLOCK)
        {
            curline.push_back(curnode);
            node.block.push_back(curline);
            curline.clear();
            continue;
        }
        else if (curnode.type == AST_ARGMAP)
        {
            if (curline.size() > 0)
            {
                Node cn = curline.back();
                curline.pop_back();
                Node new_expr_node{AST_FUNCTION_CALL};
                new_expr_node.expr.push_back(cn);
                new_expr_node.expr.push_back(curnode);
                curline.push_back(new_expr_node);
                continue;
            }
        }
        curline.push_back(curnode);
    }
    return node;
}

// build an ArgMap node from vector generated by parser.
Parser::Node Parser::Parser::build_ArgMap_from_vector(std::vector<Node> vec)
{
    Node node{AST_ARGMAP};
    Node cn;
    
    // States
    bool left_over = false;
    bool set_cn = false;

    for (int i = 0; i < vec.size(); i++)
    {
        Node curnode = vec.at(i);
        if (curnode.type == AST_ATOM)
        {
            if (curnode.atom.token.value == ",")
            {
                if (set_cn)
                {
                    node.argmap.push_back(cn);
                    left_over = false;
                    set_cn = false;
                    continue;
                }
                else 
                {
                    return cn;
                }
            }
        }
        else if (curnode.type == AST_ARGMAP)
        {
            if (set_cn)
            {
                Node new_expr_node{AST_FUNCTION_CALL};
                new_expr_node.expr.push_back(cn);
                new_expr_node.expr.push_back(curnode);
                cn = new_expr_node;
                continue;
            }
            else
            {
                return cn;
            }
        }
        left_over = true;
        cn = curnode;
        set_cn = true;
    }
    if (left_over)
    {
        node.argmap.push_back(cn);
    }
    return node;
}

// build a Block node from vector generated by parser.
Parser::Node Parser::Parser::build_Expression_from_vector(std::vector<Node> vec)
{
    Node node{AST_EXPRESSION};
    Node cn;
    for (int i = 0; i < vec.size(); i++)
    {
        Node curnode = vec.at(i);
        if (curnode.type == AST_ARGMAP)
        {
            if (node.expr.size() > 0)
            {
                node.expr.pop_back();
                Node new_expr_node{AST_FUNCTION_CALL};
                new_expr_node.expr.push_back(cn);
                new_expr_node.expr.push_back(curnode);
                curnode = new_expr_node;
            }
        }
        node.expr.push_back(curnode);
        cn = curnode;
    }
    return node;
}


Parser::Node Parser::Parser::parse_next_node()
{
    Token::Token token = stream.next();

    if (token.value == "(")
    {
        std::vector<Node> node;
        token = stream.peek();
        while (token.value != ")")
        {
            node.push_back(parse_next_node());
            if (error_found)
            {
                return Node{AST_EXPRESSION};
            }
            if (stream.eof)
            {
                error_found = true;
                ErrorType = EOF_;
                eof_error = EOF_ERROR{"Unexpected EOF while parsing expression.", token};
                return Node{AST_EXPRESSION};
            }
            token = stream.peek();
        }
        stream.next();
        return build_Expression_from_vector(node);
    }

    else if (token.value == "{")
    {
        std::vector<Node> node;
        token = stream.peek();
        while (token.value != "}")
        {
            node.push_back(parse_next_node());
            if (error_found)
            {
                return Node{AST_BLOCK};
            }
            if (stream.eof)
            {
                error_found = true;
                ErrorType = EOF_;
                eof_error = EOF_ERROR{"Unexpected EOF while parsing code.", token};
                return Node{AST_BLOCK};
            }
            token = stream.peek();
        }
        stream.next();
        return build_Block_from_vector(node);
    }

    else if (token.value == "[")
    {
        std::vector<Node> node;
        token = stream.peek();
        while (token.value != "]")
        {
            node.push_back(parse_next_node());
            if (error_found)
            {
                return Node{AST_ARGMAP};
            }
            if (stream.eof)
            {
                error_found = true;
                ErrorType = EOF_;
                eof_error = EOF_ERROR{"Unexpected EOF while parsing arguments.", token};
                return Node{AST_ARGMAP};
            }
            token = stream.peek();
        }
        stream.next();
        return build_ArgMap_from_vector(node);
    }

    else if (token.value == ")" || token.value == "]" || token.value == "}")
    {
        error_found = true;
        parsing_error = PARSING_ERROR{"Unexpected '" + token.value + "' token found while parsing.", token};
        return Node{AST_ATOM};
    }

    Node node{AST_ATOM};
    node.atom.token = token;
    return node;
}


void Parser::Parser::parse()
{
    std::vector<Node> non_sorted_ast;
    if (stream.stream.size() == 0)
    {
        return;
    }
    while (!stream.eof)
    {
        Node node = parse_next_node();
        if (error_found)
        {
            break;
        }
        non_sorted_ast.push_back(node);
    }
    ast = build_Block_from_vector(non_sorted_ast);
}


// Debugging
void Parser::Parser::debug_print(Node node, std::string indent)
{
    if (node.type == AST_BLOCK)
    {
        std::cout << indent << "<block>" << std::endl;
        for (int i = 0; i < node.block.size(); i++)
        {
            std::vector<Node> n = node.block.at(i);
            std::cout << indent + "    " << "<line>" << std::endl;
            for (int i = 0; i < n.size(); i++)
            {
                debug_print(n.at(i), indent + "        ");
            }
            std::cout << indent + "    " << "</line>" << std::endl;
        }
        std::cout << indent << "</block>" << std::endl;
    }
    else if (node.type == AST_EXPRESSION)
    {
        std::cout << indent << "<expression>" << std::endl;
        for (int i = 0; i < node.expr.size(); i++)
        {
            debug_print(node.expr.at(i), indent + "    ");
        }
        std::cout << indent << "</expression>" << std::endl;
    }
    else if (node.type == AST_ARGMAP)
    {
        std::cout << indent << "<argument map>" << std::endl;
        for (int i = 0; i < node.argmap.size(); i++)
        {
            debug_print(node.argmap.at(i), indent + "    ");
        }
        std::cout << indent << "</argument map>" << std::endl;
    }
    else if (node.type == AST_FUNCTION_CALL)
    {
        std::cout << indent << "<function>" << std::endl;
        for (int i = 0; i < node.expr.size(); i++)
        {
            debug_print(node.expr.at(i), indent + "    ");
        }
        std::cout << indent << "</function>" << std::endl;
    }
    else
    {
        std::cout << indent << "<atom>" << std::endl;
        std::cout << indent + "    " << "Value = '" << node.atom.token.value << "'," << std::endl;
        std::cout << indent + "    " << "Line Number = " << node.atom.token.line_number << "," << std::endl;
        std::cout << indent + "    " << "Line Contents = '" << node.atom.token.line << "'," << std::endl;
        std::cout << indent << "</atom>" << std::endl;
    }
}