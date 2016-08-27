#include <fstream>
#include <iostream>

namespace
{
    enum class Comparison
    {
        LESS,
        GREATER,
        EQUAL
    };

    Comparison compare(int first, int second)
    {
        if(first < second)
        {
            return Comparison::LESS;
        }
        else if(first > second)
        {
            return Comparison::GREATER;
        }
        return Comparison::EQUAL;
    }

    void print(Comparison c, char less, char greater)
    {
        switch(c)
        {
        case Comparison::LESS:
            std::cout << less;
            break;

        case Comparison::GREATER:
            std::cout << greater;
            break;

        case Comparison::EQUAL:
            break;
        }
    }
}

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    int x1;
    int x2;
    int y1;
    int y2;

    input >> x1 >> y1 >> x2 >> y2;
    while(input)
    {
        auto ew = compare(x1, x2);
        auto ns = compare(y1, y2);

        if((ew == Comparison::EQUAL) && (ns == Comparison::EQUAL))
        {
            std::cout << "here\n";
        }
        else
        {
            print(ns, 'N', 'S');
            print(ew, 'E', 'W');
            std::cout << '\n';
        }
        input >> x1 >> y1 >> x2 >> y2;
    }
    return 0;
}
