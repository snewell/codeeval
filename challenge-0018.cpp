#include <fstream>
#include <iostream>

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    int x;
    int y;
    char ch;

    input >> x >> ch >> y;
    while(input)
    {
        auto result = y;
        while(result < x)
        {
            result += y;
        }
        std::cout << result << '\n';
        input >> x >> ch >> y;
    }
}
