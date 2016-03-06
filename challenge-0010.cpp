#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::vector<char> vals;
    char ch;

    input >> ch;
    while(input)
    {
        if(std::isalpha(ch))
        {
            vals.push_back(ch);
        }
        else
        {
            input.unget();
            int count;
            input >> count;
            if(count <= vals.size())
            {
                auto it = vals.rbegin();
                std::advance(it, count - 1);
                std::cout << *it << '\n';
            }
            vals.erase(std::begin(vals), std::end(vals));
        }
        input >> ch;
    }
    return 0;
}
