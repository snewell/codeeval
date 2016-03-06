#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::vector<char> operators;
    std::vector<double> vals;
    vals.reserve(2);

    char ch;
    input.get(ch);
    while(input)
    {
        if(std::isdigit(ch))
        {
            input.unget();
            double temp;
            input >> temp;
            vals.push_back(temp);
            if(vals.size() == 2)
            {
                switch(operators.back())
                {
                case '+':
                    vals[0] += vals[1];
                    break;

                case '-':
                    vals[0] -= vals[1];
                    break;

                case '*':
                    vals[0] *= vals[1];
                    break;

                case '/':
                    vals[0] /= vals[1];
                    break;
                }
                vals.pop_back();
                operators.pop_back();
            }
        }
        else
        {
            switch(ch)
            {
            case '+':
            case '-':
            case '*':
            case '/':
                operators.push_back(ch);
                break;

            case '\n':
                std::cout << vals.back() << '\n';
                vals.pop_back();
                break;
            }
        }
        input.get(ch);
    }
    return 0;
}
