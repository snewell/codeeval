#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

namespace
{
    char constexpr LAKE = 'o';
    char constexpr TREE = '#';
    char constexpr SPLIT = '|';

    struct Map
    {
        Map(std::string data, std::size_t height, std::size_t lakes)
          : _data{std::move(data)},
            _width{_data.length() / height},
            _height{height},
            _lakeCells{lakes} { }

        struct Coord
        {
            int x;
            int y;
        };

        std::size_t countLakes() noexcept
        {
            auto ret = 0u;
            auto lastLake = 0u;
            while(_lakeCells != 0)
            {
                auto lake = _data.find(LAKE, lastLake);
                _data[lake] = TREE;
                --_lakeCells;
                ++ret;

                auto const current = getCoord(lake);
                // top row
                markTouching(Coord{current.x - 1, current.y - 1});
                markTouching(Coord{current.x,     current.y - 1});
                markTouching(Coord{current.x + 1, current.y - 1});

                // current row
                markTouching(Coord{current.x - 1, current.y});
                markTouching(Coord{current.x + 1, current.y});

                // bottom row
                markTouching(Coord{current.x - 1, current.y + 1});
                markTouching(Coord{current.x,     current.y + 1});
                markTouching(Coord{current.x + 1, current.y + 1});
                lastLake = lake + 1;
            }
            return ret;
        }

        void markTouching(Coord current) noexcept
        {
            if((current.x >= 0) && (current.y >= 0) &&
               (current.x < _width) && (current.y < _height))
            {
                // we have a valid position
                auto const index = getIndex(current);
                if(_data[index] == LAKE)
                {
                    _data[index] = TREE;
                    --_lakeCells;

                    // top row
                    markTouching(Coord{current.x - 1, current.y - 1});
                    markTouching(Coord{current.x,     current.y - 1});
                    markTouching(Coord{current.x + 1, current.y - 1});

                    // current row
                    markTouching(Coord{current.x - 1, current.y});
                    markTouching(Coord{current.x + 1, current.y});

                    // bottom row
                    markTouching(Coord{current.x - 1, current.y + 1});
                    markTouching(Coord{current.x,     current.y + 1});
                    markTouching(Coord{current.x + 1, current.y + 1});
                }
            }
        }

        Coord getCoord(std::string::size_type lake) const noexcept
        {
            return Coord{static_cast<int>(lake % _width),
                         static_cast<int>(lake / _width)};
        }

        std::size_t getIndex(Coord coord) const noexcept
        {
            return (coord.y * _width) + coord.x;
        }

        std::string _data;
        std::size_t const _width;
        std::size_t const _height;
        std::size_t _lakeCells;
    };

    Map buildMap(std::string &map)
    {
        auto lakes = 0u;
        auto height = 1u;
        // trim the blanks
        auto it = std::stable_partition(std::begin(map), std::end(map), [&lakes, &height](char ch) {
            switch(ch)
            {
            case LAKE:
                ++lakes;
            case TREE:
                return true;
                break;

            case SPLIT:
                ++height;
            default:
                return false;
            }
        });
        map.erase(it, std::end(map));

        return Map{map, height, lakes};
    }
}

int main(int argc, char ** argv)
{
    (void) argc;

    std::ifstream input{argv[1]};
    std::string data;

    std::getline(input, data);
    while(input)
    {
        auto map = buildMap(data);

#if 1
        std::cout << map.countLakes() << '\n';
#else
        auto toWrite = map._width;
        std::for_each(std::begin(map._data), std::end(map._data), [&toWrite, &map](char ch) {
            std::cout << ch;
            if((--toWrite) == 0)
            {
                toWrite = map._width;
                std::cout << '\n';
            }
        });
        std::cout << '\t' << map._lakes << "\n\n";
#endif
        std::getline(input, data);
    }
    return 0;
}
