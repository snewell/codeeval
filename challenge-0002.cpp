#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::string line;
    unsigned int count;

    input >> count;
    std::vector<std::string> result;
    result.reserve(count);

    auto finder = [&line](std::string const &s) {
        return (line.length() > s.length());
    };
    std::getline(input, line);
    std::getline(input, line);
    while(input)
    {
        if(result.size() < count)
        {
            auto it = std::find_if(std::begin(result), std::end(result), finder);
            result.insert(it, line);
        }
        else
        {
            auto it = std::find_if(std::begin(result), std::end(result), finder);
            if(it != std::end(result))
            {
                auto eraseIt = result.rbegin();
                std::advance(eraseIt, 1);
                result.erase(eraseIt.base(), std::end(result));
                result.insert(it, line);
            }
        }
        std::getline(input, line);
    }
    std::for_each(std::begin(result), std::end(result), [](std::string const &s) {
        std::cout << s << '\n';
    });
    return 0;
}
