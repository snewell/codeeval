#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    struct Data
    {
        char val;
        unsigned int count;
    };
}

int main(int argc, char ** argv)
{
    std::vector<Data> counts;
    std::ifstream input{argv[1]};
    std::string line;
    input >> line;
    while(input)
    {
        std::for_each(std::begin(line), std::end(line), [&counts](char c) {
            auto it = std::find_if(std::begin(counts), std::end(counts), [c](Data const &d) {
                return (c == d.val);
            });
            if(it != std::end(counts))
            {
                ++((*it).count);
            }
            else
            {
                counts.emplace_back(Data{c, 1});
            }
        });
        std::stable_partition(std::begin(counts), std::end(counts), [](Data const &d) {
            return (d.count == 1);
        });
        std::cout << counts.front().val << '\n';
        counts.erase(std::begin(counts), std::end(counts));
        input >> line;
    }
    return 0;
}
