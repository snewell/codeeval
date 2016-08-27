#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

namespace
{
    struct Bf
    {
        Bf(std::size_t memorySize)
        {
            my_memory.resize(memorySize, 0);
            my_dataPtr = std::begin(my_memory);
        }

        void reset()
        {
            my_dataPtr = std::begin(my_memory);
            std::transform(my_dataPtr, std::end(my_memory), my_dataPtr, [](unsigned char) {
                return 0;
            });
        }

        std::vector<unsigned char> my_memory;
        std::vector<unsigned char>::iterator my_dataPtr;
    };

    void execute(Bf &bf, std::string const &program)
    {
        auto cp = std::begin(program);
        auto const eof = std::end(program);

        while(cp != eof)
        {
            switch(*cp)
            {
            case '<':
                if(bf.my_dataPtr == std::begin(bf.my_memory))
                {
                    bf.my_dataPtr = std::end(bf.my_memory);
                }
                std::advance(bf.my_dataPtr, -1);
                break;

            case '>':
                std::advance(bf.my_dataPtr, 1);
                if(bf.my_dataPtr == std::end(bf.my_memory))
                {
                    bf.my_dataPtr = std::begin(bf.my_memory);
                }
                break;

            case '+':
                ++((*bf.my_dataPtr));
                break;

            case '-':
                --(*(bf.my_dataPtr));
                break;

            case '.':
                std:: cout << (*(bf.my_dataPtr));
                break;

            case ',':
                {
                    char ch;
                    std::cin.get(ch);
                    (*(bf.my_dataPtr)) = ch;
                }
                break;

            case '[':
                if((*(bf.my_dataPtr)) == 0)
                {
                    auto depth = 0;
                    cp = std::find_if(cp, eof, [&depth] (char ch) {
                        switch(ch)
                        {
                        case ']':
                            return (--depth) == 0;
                            break;

                        case '[':
                            ++depth;
                            break;
                        }
                        return false;
                    });
                }
                break;

            case ']':
                if((*(bf.my_dataPtr)) != 0)
                {
                    auto depth = 0;
                    std::advance(cp, 1);
                    auto newCp = std::find_if(std::string::const_reverse_iterator{cp}, program.rend(), [&depth](char ch) {
                        switch(ch)
                        {
                        case '[':
                            return (--depth) == 0;
                            break;

                        case ']':
                            ++depth;
                            break;
                        }
                        return false;
                    });
                    // advance one more step since we always move the program counter forward
                    std::advance(newCp, 1);
                    cp = newCp.base();
                }
                break;
            }
            std::advance(cp, 1);
        }
    }
}

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    std::string line;

    Bf bf{30000};

    std::getline(input, line);
    while(input)
    {
        execute(bf, line);
        bf.reset();
        std::cout << '\n';
        std::getline(input, line);
    }
    return 0;
}
