#include "util.hpp"
#include "argparse.hpp"

void usage() 
{
    std::cerr << "Usage: sogolo <FILENAME> <OPTIONS>" << std::endl;
    std::cerr << "OPTIONS:" << std::endl;
    std::cerr << "\t-h,  --help         | Show this page." << std::endl;
    std::cerr << "\t-v,  --version      | Show version number." << std::endl;
    std::cerr << "\t-t,  --read_tokens  | Read token stream." << std::endl;
    std::cerr << "\t-p,  --read_ast     | Read AST." << std::endl;
}

int main(int argc, char const *argv[]) 
{
    // Reading Arguments
    std::vector<std::string> args(argv, argv+argc);
    Sogolo::ArgumentHolder argslots(args);

    if (argslots.help || argslots.none) 
    {
        usage();
        return EXIT_SUCCESS;
    }
    if (argslots.s_version) 
    {
        std::cout << "Sogolo Development Version." << std::endl;
        return EXIT_SUCCESS;
    }
    if (argslots.filename == "") 
    {
        std::cerr << "Error: No files provided for parsing." << std::endl;
        return EXIT_FAILURE;
    }

    // Read file
    Sogolo::File code(argslots.filename);

    if (!code.exists) 
    {
        std::cerr << "Error: Can't open file '" << argslots.filename << "'." << std::endl;
        std::cerr << "No such file '" << argslots.filename << "'." << std::endl;
        return EXIT_FAILURE;
    }

    // Tokenization
    Sogolo::Lexer lexer(code.str);
    
    if (lexer.error_found)
    {
        std::cout << lexer.error.repr;
        return EXIT_FAILURE;
    }

    if (argslots.debug_tokens) 
    {
        lexer.stream.print();
        return EXIT_SUCCESS;
    }


    return EXIT_SUCCESS;
}
