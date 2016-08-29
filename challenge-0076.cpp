#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

namespace
{
    template <typename LB, typename LE, typename RB, typename RE>
    bool isRotation(LB const lStart, LE const lEnd, RB const rStart, RE const rEnd)
    {
        auto const lLen = std::distance(lStart, lEnd);
        auto const rLen = std::distance(rStart, rEnd);

        if(lLen == rLen)
        {
            // make sure we have the same lengths
            if(lLen == 0)
            {
                // if both strings are 0 we can exit now
                return true;
            }
            auto rCurrent = std::find(rStart, rEnd, *lStart);
            while(rCurrent != rEnd)
            {
                if(std::equal(rCurrent, rEnd, lStart))
                {
                    auto diff = std::distance(rCurrent, rEnd);
                    auto lMiddle = lStart;
                    std::advance(lMiddle, diff);
                    if(std::equal(lMiddle, lEnd, rStart))
                    {
                        return true;
                    }
                }
                std::advance(rCurrent, 1);
                rCurrent = std::find(rCurrent, rEnd, *lStart);
            }
        }
        return false;
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
        auto lBegin = std::begin(line);
        auto rEnd = std::end(line);
        auto lEnd = std::find(lBegin, rEnd, ',');
        auto rStart = lEnd;
        std::advance(rStart, 1);
        if(isRotation(lBegin, lEnd, rStart, rEnd))
        {
            std::cout << "True\n";
        }
        else
        {
            std::cout << "False\n";
        }
        std::getline(input, line);
    }
}
