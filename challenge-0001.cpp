#include <fstream>
#include <iostream>

namespace
{
    void doVal(unsigned int x, unsigned int y, unsigned int val)
    {
        if((val % x) == 0)
        {
            std::cout << 'F';
            if((val % y) == 0)
            {
                std::cout << 'B';
            }
        }
        else if((val % y) == 0)
        {
            std::cout << 'B';
        }
        else
        {
            std::cout << val;
        }
    }
    
    void doLine(unsigned int x, unsigned int y, unsigned int n)
    {
        unsigned int i = 1;
        doVal(x, y, i++);
        while(i <= n)
        {
            std::cout << ' ';
            doVal(x, y, i++);
        }
        std::cout << '\n';
    }
}

int main(int argc, char ** argv)
{
    (void) argc;
    unsigned int x;
    unsigned int y;
    unsigned int n;
    
    std::ifstream input{argv[1]};
    input >> x >> y >> n;
    while(input)
    {
        doLine(x, y, n);
        input >> x >> y>> n;
    }
    return 0;
}
