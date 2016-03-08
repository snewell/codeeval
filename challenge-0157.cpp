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
            coordinate{std::numeric_limits<std::uint16_t>::max()},
            visited{false}
            { }

        unsigned long score;
        std::uint16_t coordinate;
        bool visited;
    };

    void update(Maze const &m, std::vector<CellInfo> &cells, std::uint16_t newCoordiante, std::uint16_t currentCoordinate)
    {
        switch(m.my_map[newCoordiante])
        {
        case '*':
            break;

        case ' ':
            {
                auto &current = cells[currentCoordinate];
                auto &newCell = cells[newCoordiante];
                if(newCell.score == std::numeric_limits<unsigned long>::max())
                {
                    newCell.score = current.score + 1;
                    newCell.coordinate = currentCoordinate;
                }
            }
            break;
        }
    }

    void runMoves(Maze const &m, std::vector<CellInfo> &cells, std::uint16_t coordinate)
    {
        auto x = coordinate % m.my_width;
        auto y = coordinate / m.my_width;
        if(x > 0)
        {
            update(m, cells, coordinate - 1, coordinate);
        }
        if(x < (m.my_width - 1))
        {
            update(m, cells, coordinate + 1, coordinate);
        }
        if(y > 0)
        {
            update(m, cells, coordinate - m.my_width, coordinate);
        }
        if(y < (m.my_height - 1))
        {
            update(m, cells, coordinate + m.my_width, coordinate);
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
        auto const size = m.my_map.length();

        while(!found)
        {
            auto coordinate = std::uint16_t{static_cast<std::uint16_t>(startX)};
            unsigned long shortest = std::numeric_limits<unsigned long>::max();
            for(auto i = 0; i < size; ++ i)
            {
                auto &cell = pathInfo[i];
                if(!cell.visited && (cell.score < shortest))
                {
                    coordinate = i;
                    shortest = cell.score;
                }
            }
            if(coordinate == m.my_exitX)
            {
                found = true;
            }
            else
            {
                runMoves(m, pathInfo, coordinate);
                pathInfo[coordinate].visited = true;
            }
        }
        auto writeX = m.my_exitX;
        while(writeX != startX)
        {
            m.my_map[writeX] = '+';
            auto &cell = pathInfo[writeX];
            writeX = cell.coordinate;
        }
        m.my_map[startX] = '+';
    }

    Maze buildMaze(std::ifstream &input)
    {
        std::ostringstream mazeBuilder;
        std::string line;
        std::getline(input, line);
        auto width = line.length();
        std::size_t lineCount = 0;
        while(input)
        {
            ++lineCount;
            mazeBuilder << line;
            std::getline(input, line);
        }
        return Maze{mazeBuilder.str(), width, lineCount};
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

    auto m = buildMaze(input);
    solve(m);
    std::cout << m;
    return 0;
}
