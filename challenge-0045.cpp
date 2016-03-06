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
        auto rev = std::string::const_reverse_iterator{std::end(val)};
        auto mismatch = std::find_if(std::begin(val), middle, [&rev](char ch) {
            if(ch != *rev)
            {
                return true;
            }
            ++rev;
            return false;
        });
        return mismatch == middle;
    }

    template <typename T>
    T extract(std::string const &val)
    {
        std::istringstream is{val};
        T ret;
        is >> ret;
        return ret;
    }

    int reverse(std::string val)
    {
        auto middle = std::begin(val);
        std::advance(middle, std::distance(std::begin(val), std::end(val)) / 2);
        auto rev = std::string::reverse_iterator{std::end(val)};
        std::for_each(std::begin(val), middle, [&rev](char &ch) {
            std::swap(ch, *rev);
            ++rev;
        });
        return extract<int>(val);
    }

    int makePalindrome(std::string &val)
    {
        auto ret = 0;
        while(!isPalindrome(val))
        {
            auto temp = extract<int>(val) + reverse(val);
            std::ostringstream os;
            os << temp;
            val = os.str();
            ++ret;
        }
        return ret;
    }
}

int main(int argc, char ** argv)
{
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
