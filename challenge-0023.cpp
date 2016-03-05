#include <iomanip>
#include <iostream>

int main()
{
    for(auto i = 1; i < 13; ++i)
    {
        for(auto j = 1; j < 13; ++j)
        {
            std::cout << std::setw(4) << i * j;
        }
        std::cout << '\n';
    }
    return 0;
}
