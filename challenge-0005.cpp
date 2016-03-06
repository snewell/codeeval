#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::vector<int> vals;
    int val;
    input >> val;
    while(input)
    {
        vals.push_back(val);
        auto const last = vals.rend();
        auto start = vals.rbegin();
        std::advance(start, 1);
        auto it = std::find(start, last, val);
        if(it != last)
        {
            std::advance(it, 1);
            auto first = it.base();
            std::cout << *first;
            std::advance(first, 1);
            std::for_each(first, start.base(), [](int val) {
                std::cout << ' ' << val;
            });
            std::cout << '\n';
            vals.erase(std::begin(vals), std::end(vals));

            char ch;
            input.get(ch);
            while(ch != '\n')
            {
                input.get(ch);
            }
        }
        input >> val;
    }
    return 0;
}
