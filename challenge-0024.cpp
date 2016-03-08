#include <fstream>
#include <iostream>

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    int val;
    auto sum = 0;

    input >> val;
    while(input)
    {
        sum += val;
        input >> val;
    }
    std::cout << sum << '\n';
    return 0;
}
