#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    enum class Mode
    {
        INSERT,
        OVERWRITE
    };

    void overwrite(char c, std::string &s, std::size_t index)
    {
        s[index] = c;
    }

    void insert(char c, std::string &s, std::size_t index)
    {
        for(auto i = s.size() - 1; i > index; --i)
        {
            s[i] = s[i - 1];
        }
        overwrite(c, s, index);
    }

    struct Terminal
    {
        Terminal(std::size_t rows, std::size_t cols)
          : my_writeFn{overwrite},
            my_x{0},
            my_y{0}
        {
            my_data.reserve(rows);
            for(std::size_t i = 0; i < rows; ++i)
            {
                my_data.emplace_back(std::string(cols, ' '));
            }
        }

        void clear()
        {
            std::for_each(std::begin(my_data), std::end(my_data), [](std::string &s) {
                std::for_each(std::begin(s), std::end(s), [](char &c) {
                    c = ' ';
                });
            });
        }

        void clearRight()
        {
            for(std::size_t i = my_x; i < my_data[my_y].size(); ++i)
            {
                my_data[my_y][i] = ' ';
            }
        }

        void setMode(Mode m)
        {
            if(m == Mode::INSERT)
            {
                my_writeFn = insert;
            }
            else if(m == Mode::OVERWRITE)
            {
                my_writeFn = overwrite;
            }
        }

        void write(char c)
        {
            my_writeFn(c, my_data[my_y], my_x++);
            if(my_x == my_data[my_y].size())
            {
                --my_x;
            }
        }

        std::vector<std::string> my_data;

        void (*my_writeFn)(char, std::string &, std::size_t);

        std::size_t my_x;
        std::size_t my_y;
    };

    template <typename ...Ts>
    std::basic_ostream<Ts...>& operator << (std::basic_ostream<Ts...> &stream, Terminal const &t)
    {
        std::for_each(std::begin(t.my_data), std::end(t.my_data), [&stream](std::string const &s) {
            stream << s << '\n';
        });
        return stream;
    }
}

int main(int argc, char ** argv)
{
    (void) argc;
    std::ifstream input{argv[1]};
    char ch;
    input.get(ch);
    Terminal terminal{10, 10};
    while(input)
    {
        if(ch == '^')
        {
            // we have a command
            input.get(ch);
            switch(ch)
            {
            case 'c':
                terminal.clear();
                break;

            case 'h':
                terminal.my_x = terminal.my_y = 0;
                break;

            case 'b':
                terminal.my_x = 0;
                break;

            case 'd':
                ++(terminal.my_y);
                if(terminal.my_y == terminal.my_data.size())
                {
                    --(terminal.my_y);
                }
                break;

            case 'u':
                if(terminal.my_y > 0)
                {
                    --(terminal.my_y);
                }
                break;

            case 'l':
                if(terminal.my_x > 0)
                {
                    --(terminal.my_x);
                }
                break;

            case 'r':
                ++(terminal.my_x);
                if(terminal.my_x == terminal.my_data[terminal.my_y].size())
                {
                    --(terminal.my_x);
                }
                break;

            case 'e':
                terminal.clearRight();
                break;

            case 'i':
                terminal.setMode(Mode::INSERT);
                break;

            case 'o':
                terminal.setMode(Mode::OVERWRITE);
                break;

            case '^':
                terminal.write('^');
                break;

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                terminal.my_y = ch - '0';
                input.get(ch);
                terminal.my_x = ch - '0';
                break;
            }
        }
        else if(ch != '\n')
        {
            terminal.write(ch);
        }
        input.get(ch);
    }
    std::cout << terminal;
    return 0;
}
