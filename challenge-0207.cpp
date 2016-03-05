#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

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

    struct State
    {
        State(std::string map)
          : my_map{std::move(map)},
            my_size{static_cast<std::size_t>(std::sqrt(my_map.length()))},
            my_score{0},
            my_moveCost{2}
        {
            auto start = my_map.find(START);
            my_y = start / my_size;
            my_x = start % my_size;
        }

        char currentPosition() const noexcept
        {
            return my_map[(my_y * my_size) + my_x];
        }

        void clearCurrentPosition() noexcept
        {
            my_map[(my_y * my_size) + my_x] = INVALID;
        }

        char veriticalValue(int offset)
        {
            auto newY = my_y + offset;
            if((newY < 0) || (newY >= my_size))
            {
                return INVALID;
            }
            return my_map[(newY * my_size) + my_x];
        }

        char horizontalValue(int offset)
        {
            auto newX = my_x + offset;
            if((newX < 0) || (newX >= my_size))
            {
                return INVALID;
            }
            return my_map[(my_y * my_size) + newX];
        }

        State create(int xOffset, int yOffset)
        {
            State ret{*this};
            ret.my_x += xOffset;
            ret.my_y += yOffset;
            return ret;
        }

        std::string my_map;
        std::size_t my_size;
        std::int8_t my_x;
        std::int8_t my_y;
        unsigned int my_score;
        unsigned int my_moveCost;
    };

    using States = std::unordered_map<std::int32_t, State>;

    constexpr std::int32_t makeKey(State const &state)
    {
        return (state.my_x << 16) | (state.my_y << 8) | state.my_moveCost;
    }

    void addState(States &states, State state)
    {
        auto key = makeKey(state);
        auto it = states.find(key);
        if(it == std::end(states))
        {
            states.emplace(std::make_pair(key, std::move(state)));
        }
        else
        {
            if(it->second.my_score > state.my_score)
            {
                std::swap(it->second, state);
            }
        }
    }

    void runVerticalMove(State &state, States &states, int offset)
    {
        switch(state.veriticalValue(offset))
        {
        case FINISH:
        case PORT:
        case FREE:
            addState(states, state.create(0, offset));
            break;
        }
    }

    void runHorizontalMove(State &state, States &states, int offset)
    {
        switch(state.horizontalValue(offset))
        {
        case FINISH:
        case PORT:
        case FREE:
            addState(states, state.create(offset, 0));
            break;
        }
    }

    void runMoves(State &state, States &states)
    {
        runVerticalMove(state, states, -1);
        runVerticalMove(state, states,  1);
        runHorizontalMove(state, states, -1);
        runHorizontalMove(state, states,  1);
    }

    unsigned int runStates(States states)
    {
        auto ret = std::numeric_limits<unsigned int>::max();

        while(!states.empty())
        {
            auto it = std::begin(states);
            auto &state = it->second;

            switch(state.currentPosition())
            {
            case FINISH:
                state.my_score += state.my_moveCost;
                ret = std::min(ret, state.my_score);
                break;

            case PORT:
                state.my_score += state.my_moveCost;
                state.my_score += 1;
                if(state.my_moveCost == 2)
                {
                    state.my_moveCost = 1;
                }
                else
                {
                    state.my_moveCost = 2;
                }
                state.clearCurrentPosition();
                runMoves(state, states);
                break;

            case FREE:
                state.my_score += state.my_moveCost;
                // fall through intentional
            case START:
                state.clearCurrentPosition();
                runMoves(state, states);
                break;
            }

            states.erase(it);
        }
        return ret;
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
        States states;
        addState(states, State{std::move(map)});
        auto result = runStates(std::move(states));
        std::cout << result << '\n';
        std::getline(input, map);
    }
    return 0;
}
