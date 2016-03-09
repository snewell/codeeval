#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    template <typename T>
    class Stack
    {
    public:
        void push(T const &t)
        {
            my_stack.push_back(t);
        }

        T const& top() const noexcept
        {
            return my_stack.back();
        }

        void pop()
        {
            my_stack.pop_back();
        }

        std::size_t size() const noexcept
        {
            return my_stack.size();
        }

    private:
        std::vector<T> my_stack;
    };
}

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::string line;

    std::getline(input, line);
    while(input)
    {
        Stack<int> s;
        std::istringstream is{line};
        int val;
        is >> val;
        while(is)
        {
            s.push(val);
            is >> val;
        }
        if(s.size() > 0)
        {
            std::cout << s.top();
            s.pop();
        }
        while(s.size() > 1)
        {
            s.pop();
            std::cout << ' ' << s.top();
            s.pop();
        }
        std::cout << '\n';
        std::getline(input, line);
    }
    return 0;
}
