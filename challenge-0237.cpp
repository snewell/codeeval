#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

namespace
{
    int convertHexDigit(char ch)
    {
        if(std::isalpha(ch))
        {
            return std::toupper(ch) - 'A' + 10;
        }
        return ch - '0';
    }

    int readVirus(std::string::iterator begin, std::string::iterator end)
    {
        auto ret = 0;
        auto builder = 0;
        std::for_each(begin, end, [&ret, &builder](char c) {
            if(!std::isspace(c))
            {
                builder *= 16;
                builder += convertHexDigit(c);
            }
            else
            {
                ret += builder;
                builder = 0;
            }
        });
        ret += builder;
        return ret;
    }

    int readBinary(std::string::iterator begin, std::string::iterator end)
    {
        auto ret = 0;
        auto builder = 0;
        std::for_each(begin, end, [&ret, &builder](char c) {
            if(!std::isspace(c))
            {
                builder *= 2;
                builder += (c - '0');
            }
            else
            {
                ret += builder;
                builder = 0;
            }
        });
        ret += builder;
        return ret;
    }
}

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::string line;

    std::string const results[] = {"False\n", "True\n"};

    std::getline(input, line);
    while(input)
    {
        auto b = std::begin(line);
        auto e = std::end(line);
        auto m = std::find(b, e, '|');
        auto virus = readVirus(b, m);
        auto antiVirus = readBinary(m, e);
        std::cout << results[(antiVirus >= virus)];
        std::getline(input, line);
    }

    return 0;
}
