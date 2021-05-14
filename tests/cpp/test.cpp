#include <iostream>
#include <string>

class Test
{
private:
    /* data */
public:
    std::string name;

    Test(std::string& n);
    ~Test();

};

Test::Test(std::string& n)
{
    name = n;
}

Test::~Test()
{}

int main(int argc, char const *argv[])
{
    std::string name = "Tester";
    Test tester(name);

    std::cout << tester.name << std::endl;

    std::cin >> name;
    std::cout << name + "  " + tester.name << std::endl;

    return 0;
}

