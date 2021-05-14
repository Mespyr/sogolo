#include <iostream>

class User
{
public:
    virtual void output()
    {
        std::cout << "I am a user!\n";
    }
};

class Teacher : public User
{
public:
    void output()
    {
        std::cout << "I am a teacher!\n";
    }
};

int main(int argc, char const *argv[])
{
    Teacher teacher;
    User& user = teacher;


    user.output();
    teacher.output();

    return 0;
}
