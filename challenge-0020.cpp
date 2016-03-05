#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::string line;

    std::getline(input, line);
    while(input)
    {
        std::for_each(std::begin(line), std::end(line), [](char c) {
            std::cout << static_cast<char>(std::tolower(c));
        });
        std::cout << '\n';
        std::getline(input, line);
    }
    return 0;
}
