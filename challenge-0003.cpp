#include <algorithm>
#include <cmath>
#include <iostream>

namespace
{
    bool isPrime(unsigned int val)
    {
        if(val < 4)
        {
            return (val != 1);
        }
        auto upper = static_cast<unsigned int>(std::sqrt(val)) + 1;
        for(auto i = 3u; i < upper; i += 2)
        {
            if((val % i) == 0)
            {
                return false;
            }
        }
        return true;
    }

    bool isPalindrome(unsigned int val)
    {
        auto s = std::to_string(val);
        auto b = std::begin(s);
        auto middle = b;
        std::advance(middle, std::distance(b, std::end(s))/2);
        return std::equal(b, middle, s.rbegin());
    }
}

int main()
{
    for(auto i = 999u; i > 0; i -= 2)
    {
        if(isPrime(i) && isPalindrome(i))
        {
            std::cout << i << '\n';
            return 0;
        }
    }
    return 1;
}
