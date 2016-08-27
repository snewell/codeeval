#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    constexpr std::size_t MAX_SIZE = 15;

    struct Column
    {
        Column()
        {
            my_vals.reserve(MAX_SIZE);
        }

        std::vector<int> my_vals;
    };

    bool operator < (Column const &lhs, Column const &rhs)
    {
        for(auto i = 0u; i < lhs.my_vals.size(); ++i)
        {
            auto diff = lhs.my_vals[i] - rhs.my_vals[i];
            if(diff < 0)
            {
                return true;
            }
            else if(diff > 0)
            {
                return false;
            }
        }
        return false;
    }

    struct Matrix
    {
        Matrix()
        {
            my_columns.reserve(MAX_SIZE);
        }

        std::vector<Column> my_columns;
    };

    template <typename FN>
    void parseRow(std::string const &row, FN const &fn)
    {
        std::istringstream is{row};
        int val;
        is >> val;
        while(is)
        {
            fn(val);
            is >> val;
        }
    }

    Matrix parseMatrix(std::string const &s)
    {
        Matrix m;
        auto first = true;
        auto start = std::begin(s);
        while(start != std::end(s))
        {
            auto rowEnd = std::find(start, std::end(s), '|');
            if(first)
            {
                parseRow(std::string{start, rowEnd}, [&m](int val) {
                    m.my_columns.emplace_back(Column{});
                    m.my_columns.back().my_vals.push_back(val);
                });
                first = false;
            }
            else
            {
                auto index = 0;
                parseRow(std::string{start, rowEnd}, [&m, &index](int val) {
                    m.my_columns[index++].my_vals.push_back(val);
                });
            }
            if(rowEnd != std::end(s))
            {
                ++rowEnd;
            }
            start = rowEnd;
        }
        return m;
    }
}

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    std::string line;

    std::getline(input, line);
    while(input)
    {
        auto matrix = parseMatrix(line);

        std::sort(std::begin(matrix.my_columns), std::end(matrix.my_columns));
        for(decltype(matrix.my_columns.size()) i = 0; i < matrix.my_columns.size(); ++i)
        {
            for(decltype(matrix.my_columns[i].my_vals.size()) j = 0; j < matrix.my_columns[i].my_vals.size(); ++j)
            {
                if((i != 0) || (j != 0))
                {
                    std::cout << ' ';
                }
                std::cout << matrix.my_columns[j].my_vals[i];
            }
            if(i != (matrix.my_columns.size() - 1))
            {
                std::cout << " |";
            }
        }
        std::cout << "\n";

        std::getline(input, line);
    }
    return 0;
}
