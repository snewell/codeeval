#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    std::string line;

    std::getline(input, line);
    while(input)
    {
        if(!line.empty())
        {
            auto end = std::find(line.rbegin(), line.rend(), ',');
            auto pos = std::find(end, line.rend(), line.back());
            if(pos == line.rend())
            {
                std::cout << "-1\n";
            }
            else
            {
                std::cout << std::distance(std::begin(line), pos.base()) - 1 << '\n';
            }
        }
        std::getline(input, line);
    }
    return 0;
}
