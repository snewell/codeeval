#include <algorithm>
#include <fstream>
#include <iostream>

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};

    std::string word;
    input >> word;
    while(input)
    {
        std::sort(std::begin(word), std::end(word));
        std::cout << word;
        while(std::next_permutation(std::begin(word), std::end(word)))
        {
            std::cout << ',' << word;
        }
        std::cout << '\n';
        input >> word;
    }
    return 0;
}
