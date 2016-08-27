#include <fstream>
#include <iostream>
#include <string>

namespace
{
    std::string calculateLabel(int val)
    {
        std::string ret;
        ret.reserve(4);     // reserve the max for the challenge
        while(val != 0)
        {
            --val;
            auto labelChar = (val % 26);
            ret.insert(std::begin(ret), labelChar + 'A');
            val /= 26;
        }
        return ret;
    }
}

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    int val;

    input >> val;
    while(input)
    {
        std::cout << calculateLabel(val) << '\n';
        input >> val;
    }
    return 0;
}
