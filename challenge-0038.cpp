#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

namespace
{
    void trimAlphabet(std::string &alphabet)
    {
        for(auto i = 0u; i < alphabet.length(); ++i)
        {
            auto it = std::begin(alphabet);
            std::advance(it, i);
            auto val = *it;
            std::advance(it, 1);
            it = std::stable_partition(it, std::end(alphabet), [val] (char ch) {
                return (val != ch);
            });
            alphabet.erase(it, std::end(alphabet));
        }
    }

    void buildStringStep(std::size_t size, std::string const &alphabet, std::string &work, std::size_t index, bool first)
    {
        if(size != 0)
        {
            for(auto i = 0u; i < alphabet.length(); ++i)
            {
                work[index] = alphabet[i];
                buildStringStep(size - 1, alphabet, work, index + 1, first && (i == 0));
            }
        }
        else
        {
            if(!first)
            {
                std::cout << ',';
            }
            else
            {
                first = false;
            }
            std::cout << work;
        }
    }

    void printStrings(std::size_t size, std::string const &alphabet)
    {
        std::string work(size, ' ');
        buildStringStep(size, alphabet, work, 0, true);
    }
}

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    unsigned int size;
    char ch;
    std::string alphabet;

    input >> size >> ch >> alphabet;
    while(input)
    {
        std::sort(std::begin(alphabet), std::end(alphabet));
        trimAlphabet(alphabet);
        printStrings(size, alphabet);
        std::cout << '\n';
        input >> size >> ch >> alphabet;
    }
    return 0;
}