#include <fstream>
#include <iostream>
#include <unordered_map>

namespace
{
    unsigned long long countPaths(unsigned int steps)
    {
        static std::unordered_map<unsigned int, unsigned long long> counts;

        switch(steps)
        {
        case 0:
            return 0;
            break;

        case 1:
            return 1;
            break;

        case 2:
            return 2;
            break;

        default:
        {
            auto it = counts.find(steps);
            if(it != counts.end())
            {
                return it->second;
            }
            else
            {
                auto count = countPaths(steps - 1) + countPaths(steps - 2);
                counts[steps] = count;
                return count;
            }
        }
            break;
        }
    }
}

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    unsigned int val;

    input >> val;
    while(input)
    {
        std::cout << countPaths(val) << '\n';
        input >> val;
    }
    return 0;
}
