#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

namespace
{
    template <typename T>
    bool subEqual(T lStart, T lEnd, T rStart, T rEnd)
    {
        while((lStart != lEnd) && (*lStart == *rStart))
        {
            ++lStart;
            ++rStart;
        }
        return (lStart == lEnd);
    }

    bool isRotation(std::string lhs, std::string rhs)
    {
        if(lhs.length() == rhs.length())
        {
            auto const lStart = std::begin(lhs);
            auto const lEnd = std::end(lhs);

            auto const rEnd = std::end(rhs);
            auto rStart = std::find(std::begin(rhs), rEnd, lhs[0]);
            while(rStart != rEnd)
            {
                auto diff = std::distance(rStart, rEnd);
                auto lMiddle = lStart;
                std::advance(lMiddle, diff);
                if(subEqual(lStart, lMiddle, rStart, rEnd) &&
                   subEqual(lMiddle, lEnd, std::begin(rhs), rStart))
                {
                    return true;
                }
                ++rStart;
                rStart = std::find(rStart, rEnd, lhs[0]);
            }
        }
        return false;
    }
}

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::string line;
    std::getline(input, line);
    while(input)
    {
        auto split = std::find(std::begin(line), std::end(line), ',');
        std::string lhs{std::begin(line), split};
        std::string rhs{++split, std::end(line)};
        if(isRotation(std::move(lhs), std::move(rhs)))
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
