#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

namespace
{
    int digitSum(int digit)
    {
        std::ostringstream ss;
        ss << digit;
        auto s = ss.str();

        auto ret = 0;
        std::for_each(std::begin(s), std::end(s), [&ret](char c) {
            c -= '0';
            ret += (c * c);
        });
        return ret;
    }

    bool isHappy(int val)
    {
        std::set<int> visited;

        while(val != 1)
        {
            auto it = visited.find(val);
            if(it != visited.end())
            {
                return false;
            }
            visited.insert(val);

            val = digitSum(val);
        }
        return true;
    }
}

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    int val;

    input >> val;
    while(input)
    {
        std::cout << static_cast<int>(isHappy(val)) << '\n';
        input >> val;
    }
    return 0;
}
