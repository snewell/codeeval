#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::string card;

    std::getline(input, card);
    while(input)
    {
        auto sum = 0;
        auto doub = true;
        std::for_each(std::begin(card), std::end(card), [&sum, &doub](char c) {
            if(std::isdigit(c))
            {
                auto val = c - '0';
                sum += (val * ((doub) ? 2 : 1));
                doub = !doub;
            }
        });
        if((sum % 10) == 0)
        {
            std::cout << "Real\n";
        }
        else
        {
            std::cout << "Fake\n";
        }
        std::getline(input, card);
    }
    return 0;
}
