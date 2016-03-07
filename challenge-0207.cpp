#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>

namespace
{
    char constexpr START    = 'S';
    char constexpr FINISH   = 'F';
    char constexpr FREE     = '*';
    char constexpr MOUNTAIN = '^';
    char constexpr PORT     = 'P';
    char constexpr INVALID  = 'X';

    void trimMap(std::string &map)
    {
        auto it = std::stable_partition(std::begin(map), std::end(map), [](char ch) {
            switch(ch)
            {
            case START:
            case FINISH:
            case FREE:
            case MOUNTAIN:
            case PORT:
                return true;
                break;

            default:
                return false;
            }
        });
        map.erase(it, std::end(map));
    }

    struct Node
    {
        unsigned int score;
        unsigned int moveCost;
        bool visited;
    };

    struct State
    {
        State(std::string map)
          : my_map{std::move(map)},
            my_size{static_cast<std::size_t>(std::sqrt(my_map.length()))}
        {
            auto start = my_map.find(START);
            my_startY = start / my_size;
            my_startX = start % my_size;
            my_costs.resize(my_size * my_size, Node{std::numeric_limits<unsigned int>::max(), 2});
            getCost(my_startX, my_startY).score = 0;
            getCost(my_startX, my_startY).visited = true;
        }

        Node& getCost(std::size_t x, std::size_t y)
        {
            return my_costs[(y * my_size) + x];
        }

        char getMapCell(std::size_t x,std::size_t y) const noexcept
        {
            return my_map[(y * my_size) + x];
        }

        std::vector<Node> my_costs;

        std::string const my_map;
        std::size_t const my_size;
        std::size_t my_startX;
        std::size_t my_startY;
    };

    void updateCosts(State &state, unsigned newX, unsigned newY, unsigned int currentX, unsigned int currentY)
    {
        auto extraCost = 0;
        auto &cellCost = state.getCost(currentX, currentY);
        auto &newCost = state.getCost(newX, newY);
        auto newMoveCost = cellCost.moveCost;
        switch(state.getMapCell(newX, newY))
        {
        case PORT:
            extraCost += 1;
            newMoveCost = (cellCost.moveCost == 2) ? 1 : 2;;
            // fall through
        case FINISH:
        case FREE:
        case START:
            extraCost += cellCost.moveCost;
            break;

        case MOUNTAIN:
            return;
            break;
        }
        auto totalCost = cellCost.score + extraCost;
        if((newCost.score > totalCost) || (newCost.moveCost > cellCost.moveCost))
        {
            newCost.score = totalCost;
            newCost.moveCost = newMoveCost;
            newCost.visited = false;
        }
    }

    void runMoves(State &state, unsigned int x, unsigned int y)
    {
        if(x > 0)
        {
            updateCosts(state, x - 1, y, x, y);
        }
        if(x < (state.my_size - 1))
        {
            updateCosts(state, x + 1, y, x, y);
        }
        if(y > 0)
        {
            updateCosts(state, x, y - 1, x, y);
        }
        if(y < (state.my_size - 1))
        {
            updateCosts(state, x, y + 1, x, y);
        }
    }

    unsigned int runState(State state)
    {
        while(true)
        {
            auto x = state.my_startX;
            auto y = state.my_startY;
            auto currentCost = state.getCost(x, y).score;
            for(auto i = 0; i < state.my_size; ++i)
            {
                for(auto j = 0; j < state.my_size; ++j)
                {
                    if(!((i == state.my_startX) && (j == state.my_startY)))
                    {
                        auto &cost = state.getCost(i, j);
                        if(!cost.visited && (cost.score < currentCost))
                        {
                            x = i;
                            y = j;
                            currentCost = cost.score;
                        }
                    }
                }
            }
            auto &cell = state.getCost(x, y);
            if(state.getMapCell(x, y) == FINISH)
            {
                return cell.score;
            }
            runMoves(state, x, y);
            cell.visited = true;
            if((x == state.my_startX) && (y == state.my_startY))
            {
                cell.score = std::numeric_limits<unsigned int>::max();
            }
        }
    }
}

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::string map;

    std::getline(input, map);
    while(input)
    {
        trimMap(map);
        auto result = runState(State{map});
        std::cout << result << '\n';
        std::getline(input, map);
    }
    return 0;
}
