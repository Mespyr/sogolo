#include "../include/util.hpp"
#include "../include/lexer.hpp"
#include "../include/argparse.hpp"

void usage()
{
    std::cerr << "Usage: edulo <FILENAME> <OPTIONS>" << std::endl;
    std::cerr << "OPTIONS:" << std::endl;
    std::cerr << "\t-h  --help | Show this page." << std::endl;
    std::cerr << "\t-v  --version | Show version number." << std::endl;
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> args(argv, argv+argc);
    argparse::ArgumentHolder argslots = argparse::parse_args(args);

    if (argslots.help || argslots.none)
    {
        usage();
        return 0;
    }
    if (argslots.s_version)
    {
        std::cout << "Edulo Version 0.0.1" << std::endl;
        return 0;
    }

    util::FileString code = util::read(argslots.filename);
    if (!code.exists)
    {
        std::cout << "Error: Can't open file '" << argslots.filename << "'." << std::endl;
        std::cout << "No such file '" << argslots.filename << "'." << std::endl;
        return 1;
    }
    Lexer::Lexer lexer{code.str};
    lexer.tokenize();
    // lexer.stream.print();
    return 0;
}
