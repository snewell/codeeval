#include <iostream>

int main()
{
    int test = 0xAABB;
    char * p = reinterpret_cast<char *>(&test);
    if((*p) == 0xAA)
    {
        std::cout << "BigEndian\n";
    }
    else
    {
        std::cout << "LittleEndian\n";
    }
    return 0;
}
