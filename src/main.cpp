#include "../include/util.hpp"
#include "../include/lexer.hpp"
#include "../include/argparse.hpp"
#include "../include/parser.hpp"

void usage()
{
    std::cerr << "Usage: edulo <FILENAME> <OPTIONS>" << std::endl;
    std::cerr << "OPTIONS:" << std::endl;
    std::cerr << "\t-h  --help         | Show this page." << std::endl;
    std::cerr << "\t-v  --version      | Show version number." << std::endl;
    std::cerr << "\t-t  --debug_tokens | Debug token stream." << std::endl;
}

int main(int argc, char const *argv[])
{
    // Reading Arguments
    std::vector<std::string> args(argv, argv+argc);
    argparse::ArgumentHolder argslots = argparse::parse_args(args);
    if (argslots.help || argslots.none)
    {
        usage();
        return EXIT_SUCCESS;
    }
    if (argslots.s_version)
    {
        std::cout << "Edulo Version 0.0.1" << std::endl;
        return EXIT_SUCCESS;
    }
    if (argslots.filename == "")
    {
        std::cerr << "Error: No files provided for parsing." << std::endl;
        return EXIT_SUCCESS;
    }

    // Read file
    util::FileString code = util::read(argslots.filename);
    if (!code.exists)
    {
        std::cerr << "Error: Can't open file '" << argslots.filename << "'." << std::endl;
        std::cerr << "No such file '" << argslots.filename << "'." << std::endl;
        return EXIT_FAILURE;
    }

    // Tokenization
    Lexer::Lexer lexer{code.str};
    lexer.tokenize();

    if (argslots.debug_tokens)
    {
        lexer.stream.print();
        return EXIT_SUCCESS;
    }

    // Parsing
    Parser::Parser parser{lexer.stream};
    parser.parse();
    
    if (parser.error_found)
    {
        std::cout << "\x1B[31m" << parser.get_error() << "\033[0m";
        return 1;
    }

    if (argslots.debug_ast)
    {
        parser.debug_print(parser.ast);
    }
    return EXIT_SUCCESS;
}
