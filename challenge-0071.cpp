#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

namespace
{
    void reverseChunks(std::vector<int> &vals, int count)
    {
        auto const end = std::end(vals);
        auto current = std::begin(vals);
        while(std::distance(current, end) >= count)
        {
            auto nextCurrent = current;
            std::advance(nextCurrent, count);
            auto mid = current;
            std::advance(mid, count / 2);
            auto revIt = std::vector<int>::reverse_iterator{nextCurrent};
            std::for_each(current, mid, [&revIt](int &val) {
                std::swap(val, *revIt);
                ++revIt;
            });
            current = nextCurrent;
        }
    }
}

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    int val;

    input >> val;
    while(input)
    {
        std::vector<int> vals;
        vals.push_back(val);
        char ch;
        input.get(ch);
        while(ch == ',')
        {
            input >> val;
            vals.push_back(val);
            input.get(ch);
        }
        // ch is a semi-colon
        input >> val;
        reverseChunks(vals, val);
        auto it = std::begin(vals);
        std::cout << *it;
        ++it;
        std::for_each(it, std::end(vals), [](int val) {
            std::cout << ',' << val;
        });
        std::cout << '\n';
        input >> val;
    }
    return 0;
}
