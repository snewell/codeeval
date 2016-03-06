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
        std::transform(std::begin(line), std::end(line), std::begin(line), [](char c) {
            return static_cast<char>(std::tolower(c));
        });
        std::cout << line << '\n';
        std::getline(input, line);
    }
    return 0;
}
