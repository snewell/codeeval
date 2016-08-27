#include <fstream>
#include <iostream>

namespace
{
    constexpr unsigned int buildBitMask(int bit)
    {
        return 1 << (bit - 1);
    }

    constexpr int getBit(int val, int bit)
    {
        return (val & buildBitMask(bit)) >> (bit - 1);
    }

    constexpr bool bitsEqual(int val, int bit1, int bit2)
    {
        return getBit(val, bit1) == getBit(val, bit2);
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
        int bit1;
        int bit2;
        char ch;
        input.get(ch);
        input >> bit1;
        input.get(ch);
        input >> bit2;

        if(bitsEqual(val, bit1, bit2))
        {
            std::cout << "true\n";
        }
        else
        {
            std::cout << "false\n";
        }

        input >> val;
    }
    return 0;
}
