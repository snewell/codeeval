#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    std::string line;

    std::getline(input, line);
    while(input)
    {
        auto it = std::find(std::begin(line), std::end(line), ',');
        auto scrubbed = std::string{std::begin(line), it};
        std::advance(it, 2);
        auto erase = std::stable_partition(std::begin(scrubbed), std::end(scrubbed), [&line, it](char ch) {
            auto contains = std::find(it, std::end(line), ch);
            return (contains == std::end(line));
        });
        scrubbed.erase(erase, std::end(scrubbed));
        std::cout << scrubbed << '\n';
        std::getline(input, line);
    }
    return 0;
}
