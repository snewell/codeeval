#include <iostream>
#include <string>

int main()
{
    std::string const messages[] = {"BigEndian\n", "LittleEndian\n"};
    auto test = 1;
    auto * p = reinterpret_cast<char *>(&test);
    std::cout << messages[*p];
    return 0;
}
