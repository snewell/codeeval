#include <fstream>
#include <iomanip>
#include <iostream>

namespace
{
    void printNibble(std::uint8_t val, bool leadingZeros)
    {
        auto printVal = 0;
        if(val & 0x01)
        {
            printVal += 1;
        }
        if(val & 0x02)
        {
            printVal += 10;
        }
        if(val & 0x04)
        {
            printVal += 100;
        }
        if(val & 0x08)
        {
            printVal += 1000;
        }
        if(leadingZeros)
        {
            std::cout << std::setw(4) << std::setfill('0') << printVal;
        }
        else if(printVal > 0)
        {
            std::cout << printVal;
        }
    }

    void printByte(std::uint8_t val, bool leadingZeroes)
    {
        printNibble((val >> 4), leadingZeroes);
        printNibble((val & 0x0F), leadingZeroes || (val > 0x0F));
    }
}

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::uint32_t val;

    input >> val;
    while(input)
    {
        if(val > 0)
        {
            printByte((val >> 24) & 0xFF, false);
            printByte((val >> 16) & 0xFF, (val > 0xFFFFFF));
            printByte((val >>  8) & 0xFF, (val > 0xFFFF));
            printByte((val >>  0) & 0xFF, (val > 0xFF));
            std::cout << '\n';
        }
        else
        {
            std::cout << "0\n";
        }
        input >> val;
    }
    return 0;
}
