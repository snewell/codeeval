#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    struct Maze
    {
        Maze(std::string map, std::size_t width, std::size_t height)
          : my_map{std::move(map)},
            my_width{width},
            my_height{height}
        {
            my_exitX = my_map.find(' ', my_width * (my_height - 1));
            my_exitX %= my_height;
        }

        std::string my_map;
        std::size_t const my_width;
        std::size_t const my_height;
        std::size_t my_exitX;
    };

    constexpr std::uint32_t makeStateKey(std::uint16_t x, std::uint16_t y)
    {
        return ((x << 16) | y);
    }

    struct CellInfo
    {
        CellInfo()
          : score{std::numeric_limits<unsigned long>::max()},
            x{std::numeric_limits<std::uint16_t>::max()},
            y{std::numeric_limits<std::uint16_t>::max()},
            visited{false}
            { }

        unsigned long score;
        std::uint16_t x;
        std::uint16_t y;
        bool visited;
    };

    void update(Maze const &m, std::vector<CellInfo> &cells, std::uint16_t newX, std::uint16_t newY, std::uint16_t currentX, std::uint16_t currentY)
    {
        switch(m.my_map[(newY * m.my_width) + newX])
        {
        case '*':
            break;

        case ' ':
            {
                auto &current = cells[(currentY * m.my_width) + currentX];
                auto &newCell = cells[(newY * m.my_width) + newX];
                if(newCell.score == std::numeric_limits<unsigned long>::max())
                {
                    newCell.score = current.score + 1;
                    newCell.x = currentX;
                    newCell.y = currentY;
                }
            }
            break;
        }
    }

    void runMoves(Maze const &m, std::vector<CellInfo> &cells, std::uint16_t x, std::uint16_t y)
    {
        if(x > 0)
        {
            update(m, cells, x - 1, y, x, y);
        }
        if(x < (m.my_width - 1))
        {
            update(m, cells, x + 1, y, x, y);
        }
        if(y > 0)
        {
            update(m, cells, x, y - 1, x, y);
        }
        if(y < (m.my_height - 1))
        {
            update(m, cells, x, y + 1, x, y);
        }
    }

    void solve(Maze &m)
    {
        std::vector<CellInfo> pathInfo;
        pathInfo.resize(m.my_map.length());
        auto found = false;
        auto startX = m.my_map.find(' ');
        pathInfo[startX].score = 0;
        pathInfo[startX].visited = true;

        while(!found)
        {
            auto x = std::uint16_t{static_cast<std::uint16_t>(startX)};
            auto y = std::uint16_t{0};
            unsigned long shortest = std::numeric_limits<unsigned long>::max();
            for(auto i = 0; i < m.my_width; ++i)
            {
                for(auto j = 0; j < m.my_height; ++j)
                {
                    auto &cell = pathInfo[(j * m.my_width) + i];
                    if(!cell.visited && (cell.score < shortest))
                    {
                        x = i;
                        y = j;
                        shortest = cell.score;
                    }
                }
            }
            if((x == m.my_exitX) && (y == (m.my_height - 1)))
            {
                found = true;
            }
            else
            {
                runMoves(m, pathInfo, x, y);
                pathInfo[(y * m.my_width) + x].visited = true;
            }
        }
        auto writeX = m.my_exitX;
        auto writeY = m.my_height - 1;
        while(writeY != 0)
        {
            m.my_map[(writeY * m.my_width) + writeX] = '+';
            auto &cell = pathInfo[(writeY * m.my_width) + writeX];
            writeY = cell.y;
            writeX = cell.x;
        }
        m.my_map[(writeY * m.my_width) + writeX] = '+';
    }

    template <typename ...Ts>
    std::basic_ostream<Ts...>& operator << (std::basic_ostream<Ts...> &os, Maze const &m)
    {
        for(auto i = 0; i < m.my_height; ++i)
        {
            os << m.my_map.substr(i * m.my_height, m.my_width) << '\n';
        }
        return os;
    }
}

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::string line;
    std::ostringstream mazeBuilder;
    std::size_t lineCount = 0;

    std::getline(input, line);
    auto width = line.length();
    while(input)
    {
        ++lineCount;
        mazeBuilder << line;
        std::getline(input, line);
    }
    Maze m{mazeBuilder.str(), width, lineCount};
    solve(m);
    std::cout << m;
    return 0;
}
