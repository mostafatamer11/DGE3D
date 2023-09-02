#include <iostream>

int main(int argc, const char* argv[])
{
    for (short i = 0; i < argc; ++i)
    {
        std::cout << argv[i] << "-";
    }
    std::cout << "\b" << std::endl;
}