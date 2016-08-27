#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    std::string s;
    std::getline(input, s);
    while(input)
    {
        std::cout << s << '\n';
        std::getline(input, s);
    }
    return 0;
}
