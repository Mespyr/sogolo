#include <parser.hpp>


namespace Sogolo
{
    // Parser Constructor
    Parser::Parser(TokenStream& s)
    {
        stream = s;
        parse();
    }
    
    Parser::~Parser()
    {}

    // build a Block node from vector generated by parser.
    Node Parser::build_Block_from_vector(std::vector<Node> vec, std::string line, unsigned int line_number) 
    {
        Node node;
        node.type = NODE_BLOCK;

        node.line = line;
        node.line_number = line_number;

        Node curline;
        curline.type = NODE_LINE;


        for (int i = 0; i < vec.size(); i++) 
        {
            Node curnode = vec.at(i);
            if (curnode.type == NODE_ATOM) 
            {
                if (curnode.value == ";") 
                {
                    curline.line = curnode.line;
                    curline.line_number = curnode.line_number;

                    node.nodes.push_back(curline);
                    curline.nodes.clear();
                    continue;
                }
            }
            
            else if (curnode.type == NODE_BLOCK) 
            {
                curline.line = curnode.line;
                curline.line_number = curnode.line_number;

                curline.nodes.push_back(curnode);
                node.nodes.push_back(curline);
                curline.nodes.clear();
                continue;
            }
            
            else if (curnode.type == NODE_ARGMAP) 
            {
                if (curline.nodes.size() > 0) 
                {
                    Node cn = curline.nodes.back();
                    curline.nodes.pop_back();
                    Node new_expr_node;
                    new_expr_node.type = NODE_FUNCTION_CALL;

                    new_expr_node.nodes.push_back(cn);
                    new_expr_node.nodes.push_back(curnode);
                    curline.nodes.push_back(new_expr_node);
                    continue;
                }
                else 
                { 
                    error_found = true;
                    return curnode;
                }
            }
            
            curline.nodes.push_back(curnode);
        }
        return node;
    }

    // build an ArgMap node from vector generated by parser.
    Node Parser::build_ArgMap_from_vector(std::vector<Node> vec, std::string line, unsigned int line_number) 
    {
        Node node;
        node.type = NODE_ARGMAP;

        node.line = line;
        node.line_number = line_number;

        Node cn;
        
        // States
        bool left_over = false;
        bool set_cn = false;

        for (int i = 0; i < vec.size(); i++) 
        {
            Node curnode = vec.at(i);
            if (curnode.type == NODE_ATOM) {
                if (curnode.value == ",") 
                {
                    if (set_cn) 
                    {
                        node.nodes.push_back(cn);
                        left_over = false;
                        set_cn = false;
                        continue;
                    }
                    else
                    {
                        error_found = true;
                        return cn;
                    }
                }
            }
            else if (curnode.type == NODE_ARGMAP) 
            {
                if (set_cn) 
                {
                    Node new_expr_node;
                    new_expr_node.type = NODE_FUNCTION_CALL;

                    new_expr_node.nodes.push_back(cn);
                    new_expr_node.nodes.push_back(curnode);
                    cn = new_expr_node;
                    continue;
                }
                else 
                {
                    error_found = true;
                    return curnode;
                }
            }
            left_over = true;
            cn = curnode;
            set_cn = true;
        }
        if (left_over)
            node.nodes.push_back(cn);

        return node;
    }

    // build a Block node from vector generated by parser.
    Node Parser::build_Expression_from_vector(std::vector<Node> vec, std::string line, unsigned int line_number) 
    {
        Node node;
        node.type = NODE_EXPRESSION;

        node.line = line;
        node.line_number = line_number;

        Node cn;
        for (int i = 0; i < vec.size(); i++) 
        {
            Node curnode = vec.at(i);
            if (curnode.type == NODE_ARGMAP) 
            {
                if (node.nodes.size() > 0) 
                {
                    node.nodes.pop_back();

                    Node new_expr_node;
                    new_expr_node.type = NODE_FUNCTION_CALL;

                    new_expr_node.nodes.push_back(cn);
                    new_expr_node.nodes.push_back(curnode);
                    curnode = new_expr_node;
                }
                else 
                {
                    error_found = true;
                    return curnode;
                }
            }
            node.nodes.push_back(curnode);
            cn = curnode;
        }
        return node;
    }


    Node Parser::parse_next_node()
    {
        Token token = stream.next();

        if (token.value == "(") 
        {
            std::vector<Node> node;

            unsigned int line_number = token.line_number;
            const std::string& line = token.line;

            token = stream.peek();
            while (token.value != ")") 
            {
                node.push_back(parse_next_node());
                if (error_found)
                    return Node();
                if (stream.eof) 
                {
                    error_found = true;
                    return Node();
                }
                token = stream.peek();
            }
            stream.next();
            return build_Expression_from_vector(node, line, line_number);
        }

        else if (token.value == "{") 
        {
            std::vector<Node> node;

            unsigned int line_number = token.line_number;
            const std::string& line = token.line;

            token = stream.peek();
            while (token.value != "}") 
            {
                node.push_back(parse_next_node());

                if (error_found)
                    return Node();
                
                if (stream.eof) 
                {
                    error_found = true;
                    return Node();
                }
                token = stream.peek();
            }
            stream.next();
            return build_Block_from_vector(node, line, line_number);
        }

        else if (token.value == "[") 
        {
            std::vector<Node> node;

            unsigned int line_number = token.line_number;
            std::string line = token.line;

            token = stream.peek();

            while (token.value != "]") 
            {
                node.push_back(parse_next_node());
                if (error_found)
                    return Node();
                if (stream.eof) 
                {
                    error_found = true;
                    return Node();
                }
                token = stream.peek();
            }
            stream.next();
            return build_ArgMap_from_vector(node, line, line_number);
        }

        else if (token.value == ")" || token.value == "]" || token.value == "}") 
        {
            error_found = true;
            return Node();
        }

        // If node is a symbol.
        Node n(NODE_ATOM, token.line, token.line_number, token.value);
        
        // std::cout << token.value + "  " << token.line_number << std::endl;
        // std::cout << n.value + "  " << n.line_number << std::endl << std::endl;

        n.atom_type = NODE_SYMBOL;
        return n;
    }

    void Parser::parse()
    {
        std::vector<Node> non_sorted_ast;
        if (stream.stream.size() == 0)
            return;
        while (!stream.eof) 
        {
            Node n = parse_next_node();
            if (error_found)
                return;
            non_sorted_ast.push_back(n);
        }
        ast = build_Block_from_vector(non_sorted_ast, "", 1);
    }


    // Debugging
    void Parser::debug_print_vector(Node node, std::string indent) {
        for (int i = 0; i < node.nodes.size(); i++)
            debug_print(node.nodes.at(i), indent+"    ");
    }


    void Parser::debug_print(Node node, std::string indent) {
        if (node.type == NODE_BLOCK) {
            std::cout << indent << "<block>" << std::endl;
            debug_print_vector(node, indent);
            std::cout << indent << "</block>" << std::endl;
        }
        else if (node.type == NODE_EXPRESSION) {
            std::cout << indent << "<expression>" << std::endl;
            debug_print_vector(node, indent);
            std::cout << indent << "</expression>" << std::endl;
        }
        else if (node.type == NODE_ARGMAP) {
            std::cout << indent << "<argument map>" << std::endl;
            debug_print_vector(node, indent);
            std::cout << indent << "</argument map>" << std::endl;
        }
        else if (node.type == NODE_FUNCTION_CALL) {
            std::cout << indent << "<function>" << std::endl;
            debug_print_vector(node, indent);
            std::cout << indent << "</function>" << std::endl;
        }
        else if (node.type == NODE_LINE) {
            std::cout << indent << "<line>" << std::endl;
            debug_print_vector(node, indent);
            std::cout << indent << "</line>" << std::endl;
        }
        else {
            std::cout << indent << "<atom>" << std::endl;
            std::cout << indent + "    " << "Value = '" << node.value << "'," << std::endl;
            std::cout << indent + "    " << "Line Number = " << node.line_number << "," << std::endl;
            std::cout << indent + "    " << "Line Contents = '" << node.line << "'," << std::endl;
            // std::cout << indent + "    " << "Type = " << get_type(node.atom_type) << std::endl;
            std::cout << indent << "</atom>" << std::endl;
        }
    }


} // namespace Sogolo
