#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
        Node()
        {
            score[0] = score[1] = std::numeric_limits<unsigned int>::max();
            visited[0] = visited[1] = false;
        }

        unsigned int score[2];
        bool visited[2];
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
            my_costs.resize(my_size * my_size, Node{});
            getCost(my_startX, my_startY).score[0] = 0;
            getCost(my_startX, my_startY).visited[0] = true;
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

    void updateState(Node &cell, int method, unsigned int totalCost)
    {
        if(cell.score[method] > totalCost)
        {
            cell.score[method] = totalCost;
        }
    }

    void updateCosts(State &state, int method, unsigned newX, unsigned newY, unsigned int currentX, unsigned int currentY)
    {
        auto &cellCost = state.getCost(currentX, currentY);
        auto &newCost = state.getCost(newX, newY);
        switch(state.getMapCell(newX, newY))
        {
        case PORT:
            if(method == 0)
            {
                // create a sea path and fall through in case we skip the water
                updateState(newCost, 1, cellCost.score[method] + 3);
            }
            else
            {
                // go back to land
                updateState(newCost, 0, cellCost.score[method] + 2);
                break;
            }

        case FINISH:
        case FREE:
        case START:
            updateState(newCost, method, cellCost.score[method] + ((method == 0) ? 2 : 1));
            break;

        case MOUNTAIN:
            return;
            break;
        }
    }

    void runMoves(State &state, int method, unsigned int x, unsigned int y)
    {
        if(x > 0)
        {
            updateCosts(state, method, x - 1, y, x, y);
        }
        if(x < (state.my_size - 1))
        {
            updateCosts(state, method, x + 1, y, x, y);
        }
        if(y > 0)
        {
            updateCosts(state, method, x, y - 1, x, y);
        }
        if(y < (state.my_size - 1))
        {
            updateCosts(state, method, x, y + 1, x, y);
        }
    }

    unsigned int runState(State state)
    {
        while(true)
        {
            auto x = state.my_startX;
            auto y = state.my_startY;
            auto method = 0;
            auto currentCost = state.getCost(x, y).score[0];
            for(auto i = 0; i < state.my_size; ++i)
            {
                for(auto j = 0; j < state.my_size; ++j)
                {
                    if(!((i == state.my_startX) && (j == state.my_startY)))
                    {
                        auto &cost = state.getCost(i, j);
                        for(auto k = 0; k < 2; ++k)
                        {
                            if(!cost.visited[k] && (cost.score[k] < currentCost))
                            {
                                x = i;
                                y = j;
                                currentCost = cost.score[k];
                                method = k;
                            }
                        }
                    }
                }
            }
            auto &cell = state.getCost(x, y);
            if((state.getMapCell(x, y) == FINISH) && (method == 0))
            {
                // we're at the finish node and we're on land
                return cell.score[method];
            }
            runMoves(state, method, x, y);
            cell.visited[method] = true;
            if((x == state.my_startX) && (y == state.my_startY))
            {
                cell.score[0] = std::numeric_limits<unsigned int>::max();
                cell.score[1] = std::numeric_limits<unsigned int>::max();
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
