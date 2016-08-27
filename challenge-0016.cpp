#include <fstream>
#include <iostream>

namespace
{
    unsigned int countOnes(int val)
    {
        auto ret = 0u;
        while(val)
        {
            ret += (val & 0x1);
            val >>= 1;
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
        std::cout << countOnes(val) << '\n';
        input >> val;
    }
    return 0;
}
