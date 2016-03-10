#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    std::vector<std::string>::iterator orderChunk(std::vector<std::string>::iterator start,
                                                  std::vector<std::string>::iterator end)
    {
        while(start != end)
        {
            auto offset = std::begin(*start);
            std::advance(offset, 1);
            auto offsetEnd = std::end(*start);
            auto next = std::find_if(start, end, [offset, offsetEnd](std::string const &s) {
                return std::equal(offset, offsetEnd, std::begin(s));
            });
            std::advance(start, 1);
            if(next != end)
            {
                std::rotate(start, next, end);
            }
            else
            {
                return start;
            }
        }
        return end;
    }

    void order(std::vector<std::string> &strips)
    {
        auto end = std::end(strips);
        auto middle = orderChunk(std::begin(strips), std::end(strips));
        while(middle != end)
        {
            auto old = *(std::begin(strips));
            std::rotate(std::begin(strips), middle, end);
            // this is a workaround since gcc doesn't support rotate that returns an interator
            end = std::find(std::begin(strips), std::end(strips), old);
            middle = orderChunk(std::begin(strips), end);
        }
    }
}

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::string line;

    std::getline(input, line);
    while(input)
    {
        std::vector<std::string> strips;
        auto it = std::find(std::begin(line), std::end(line), '|');
        std::advance(it, 1);
        while(it != std::end(line))
        {
            auto next = std::find(it, std::end(line), '|');
            strips.emplace_back(std::string{it, next});
            std::advance(next, 1);
            it = next;
        }
        order(strips);
        auto printIt = std::begin(strips);
        std::cout << *printIt;
        std::advance(printIt, 1);
        std::for_each(printIt, std::end(strips), [](std::string const &s) {
            std::cout << s.back();
        });
        std::cout << '\n';
        std::getline(input, line);
    }
    return 0;
}
