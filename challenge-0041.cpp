#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    unsigned int size;
    input >> size;
    while(input)
    {
        std::vector<unsigned int> vals;
        vals.reserve(size);
        for(unsigned int i{0}; i < size; ++i)
        {
            input.get();
            unsigned int val;
            input >> val;
            vals.push_back(val);
        }
        std::sort(std::begin(vals), std::end(vals));
        for(decltype(vals.size()) i = 0; i < vals.size(); ++i)
        {
            if(vals[i] == vals[i + 1])
            {
                std::cout << vals[i] << '\n';
                break;
            }
        }
        input >> size;
    }
    return 0;
}
