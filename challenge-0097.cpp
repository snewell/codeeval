#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
    void extractName(std::string data, std::string key)
    {
        std::istringstream is{key};
        int val;

        is >> val;
        while(is)
        {
            std::cout << data[val - 1];
            is >> val;
        }
        std::cout << '\n';
    }
}

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    std::string line;

    std::getline(input, line);
    while(input)
    {
        if(!line.empty())
        {
            auto it = std::find(std::begin(line), std::end(line), '|');
            extractName(std::string{std::begin(line), it}, std::string{it + 1, std::end(line)});
        }
        std::getline(input, line);
    }
    return 0;
}
