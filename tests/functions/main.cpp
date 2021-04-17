#include <stdio.h>
#include <string>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::string str = "h`\neqe.936ewj";
    int i = 0;
    while (isalnum(str[i])) 
        i++;
    printf ("The first %d characters are alphanumeric.\n",i);
    return 0;
}
