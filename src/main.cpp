#include "../include/util.hpp"
#include "../include/lexer.hpp"

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        std::cout << "Error: No files provided for `edulo`." << std::endl;
        return 1;
    }
    util::FileString code = util::read(argv[1]);
    if (!code.exists)
    {
        std::cout << "Error: Can't open file '" << argv[1] << "'." << std::endl;
        std::cout << "No such file '" << argv[1] << "'." << std::endl;
        return 1;
    }
    Lexer::Lexer lexer{code.str};
    lexer.tokenize();
    // lexer.stream.print();
    return 0;
}
