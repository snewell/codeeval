#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace
{
    std::vector<std::string>::iterator orderChunk(std::vector<std::string>::iterator start,
                                                  std::vector<std::string>::iterator end)
    {
        auto const realStart = start;
        auto retry = end;
        std::stack<std::vector<std::string>::iterator> loopPoints;
        while(start != end)
        {
            // build up a predicate for strings we'll accept as "next" after the one we're
            // currently looking at
            auto offset = std::begin(*start);
            std::advance(offset, 1);
            auto offsetEnd = std::end(*start);
            auto pred = [offset, offsetEnd](std::string const &s) {
                return std::equal(offset, offsetEnd, std::begin(s));
            };
            auto prev = start;
            std::advance(start, 1);
            auto next = std::find_if(start, end, pred);
            if(next != end)
            {
                std::swap(*start, *next);
                // see if there are any other strings that match what we're expecting
                auto temp = next;
                std::advance(temp, 1);
                temp = std::find_if(temp, end, pred);
                while(temp != end)
                {
                    if((*start != *temp) && (start != retry))
                    {
                        //we got one, store our current position so we can try other options
                        loopPoints.push(start);
                    }
                    std::advance(temp, 1);
                    temp = std::find_if(temp, end, pred);
                }
            }
            else
            {
#if 0
                std::for_each(realStart, start, [](std::string const &s) {
                    std::cout << s << '\n';
                });
#endif
                // couldn't find something that follows our current string, make sure
                // we don't have anything earlier in the list (means we looped)
                auto check = std::find_if(realStart, end, pred);
                if(check == end)
                {
                    // we know that we have the correct order here
                    return start;
                }
                else if(loopPoints.size() != 0)
                {
                    // we have a loop, so go back to whatever the first cycle point is
                    // and try again
                    start = loopPoints.top();
                    retry = start;
                    auto temp = start;
                    std::advance(temp, 1);
                    std::rotate(start, temp, end);
                    std::advance(start, -1);
                    loopPoints.pop();
                }
            }
        }
        return end;
    }

    std::vector<std::string>::iterator order(std::vector<std::string> &strips)
    {
        auto count = 0;
        auto end = std::end(strips);
        auto middle = orderChunk(std::begin(strips), std::end(strips));
        while(middle != end)
        {
            auto old = *(std::begin(strips));
            std::rotate(std::begin(strips), middle, end);
            // this is a workaround since gcc doesn't support rotate that returns an interator
            end = std::find(std::begin(strips), std::end(strips), old);
            ++count;
            if(count == 4)
            {
                //return end;
            }
            middle = orderChunk(std::begin(strips), end);
        }
        return std::begin(strips);
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
        auto printIt = order(strips);
#if 1
        std::cout << *printIt;
        std::advance(printIt, 1);
        std::for_each(printIt, std::end(strips), [](std::string const &s) {
            std::cout << s.back();
        });
        std::cout << '\n';
#else
        std::for_each(std::begin(strips), std::end(strips), [](std::string const &s) {
            std::cout << s << '\n';
        });
        std::cout << "\n\n\n";
#endif
        std::getline(input, line);
    }
    return 0;
}
