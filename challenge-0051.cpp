#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <cmath>
#include <vector>

namespace
{
    struct Point
    {
        Point(int x, int y)
          : my_x{x},
            my_y{y}
        {
        }

        long long my_x;
        long long my_y;
    };

}

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    unsigned int count;
    input >> count;
    while(input)
    {
        if(count > 0)
        {
            std::vector<Point> points;
            points.reserve(count);
            int x;
            int y;
            while(count > 0)
            {
                input >> x >> y;
                points.emplace_back(Point{x, y});
                --count;
            }
            auto shortest = std::numeric_limits<long long>::max();
            for(auto first = std::begin(points); first != std::end(points); ++first)
            {
                auto second = first;
                std::advance(second, 1);
                std::for_each(second, std::end(points), [first, &shortest](Point const &p) {
                    auto dx = std::abs((*first).my_x - p.my_x);
                    auto dy = std::abs((*first).my_y - p.my_y);
                    auto temp = (dx * dx) + (dy * dy);
                    shortest = std::min(shortest, temp);
                });
            }
            auto distance = std::sqrt(shortest);
            if(distance > 10000)
            {
                std::cout << "INFINITY\n";
            }
            else
            {
                std::cout << std::fixed << std::setprecision(4) << distance << '\n';
            }
        }
        input >> count;
    }
    return 0;
}
