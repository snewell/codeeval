#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char ** argv)
{
    std::vector<std::string> strings;
    std::ifstream input{argv[1]};
   
    std::string line;
    std::getline(input, line);
    while(input)
    {
        auto previous = std::begin(line);
        while(previous != std::end(line))
        {
            auto it = std::find(previous, std::end(line), ' ');
            strings.emplace_back(std::string{previous, it});
            if(it != std::end(line))
            {
                ++it;
            }
            previous = it;
        }
        if(strings.size() > 0)
        {
            auto start = strings.rbegin();
            std::cout << *start;
            ++start;
            std::for_each(start, strings.rend(), [](std::string const &val) {
                std::cout << ' ' << val;
            });
            strings.erase(std::begin(strings), std::end(strings));
            std::cout << '\n';
        }
        std::getline(input, line);
    }
    return 0;
}
