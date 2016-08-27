#include <fstream>
#include <iostream>
#include <unordered_map>

namespace
{
    unsigned int fib(int val)
    {
        static std::unordered_map<int, unsigned int> cache;

        switch(val)
        {
        case 0:
        case 1:
            return val;
            break;

        default:
            {
                auto it = cache.find(val);
                if(it != cache.end())
                {
                    return it->second;
                }
                auto result = fib(val - 2) + fib(val - 1);
                cache[val] = result;
                return result;
            }
            break;
        }
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
        std::cout << fib(val) << '\n';
        input >> val;
    }
    return 0;
}
