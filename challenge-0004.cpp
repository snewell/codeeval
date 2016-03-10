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
        else if((val & 0x01) == 0)
        {
            // we have an even number greater than 2
            return false;
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
}

int main()
{
    auto sum = 2u;
    auto count = 1;
    auto i = 3u;
    while(count < 1000)
    {
        if(isPrime(i))
        {
            sum += i;
            ++count;
        }
        i += 2;
    }
    std::cout << sum << '\n';
    return 0;
}
