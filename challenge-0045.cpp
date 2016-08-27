#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
    bool isPalindrome(std::string const &val)
    {
        auto middle = std::begin(val);
        std::advance(middle, std::distance(std::begin(val), std::end(val)) / 2);
        return std::equal(std::begin(val), middle, val.rbegin());
    }

    template <typename T>
    T extract(std::string const &val)
    {
        std::istringstream is{val};
        T ret;
        is >> ret;
        return ret;
    }

    unsigned long long reverse(std::string val)
    {
        std::reverse(std::begin(val), std::end(val));
        return extract<unsigned long long>(val);
    }

    int makePalindrome(std::string &val)
    {
        auto ret = 0;
        while(!isPalindrome(val))
        {
            auto temp = extract<unsigned long long>(val) + reverse(val);
            val = std::to_string(temp);
            ++ret;
        }
        return ret;
    }
}

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    std::string val;

    input >> val;
    while(input)
    {
        auto count = makePalindrome(val);
        std::cout << count << ' ' << val << '\n';
        input >> val;
    }
    return 0;
}
