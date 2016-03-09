#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    double val;

    std::vector<double> vals;
    input >> val;
    while(input)
    {
        auto it = std::lower_bound(std::begin(vals), std::end(vals), val);
        vals.insert(it, val);
        char ch;
        input.get(ch);
        if(ch == '\n')
        {
            it = std::begin(vals);
            std::cout << std::fixed << std::setprecision(3) << *it;
            std::advance(it, 1);
            std::for_each(it, std::end(vals), [](double val) {
                std::cout << ' ' << std::fixed << std::setprecision(3) << val;
            });
            vals.clear();
            std::cout << '\n';
        }
        input >> val;
    }
    return 0;
}
