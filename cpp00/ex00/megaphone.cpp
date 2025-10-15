#include <iostream>

int main(int c, char **buf)
{

    if (c == 1)
    {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    }
    else {
        for (int i = 1; i < c; i++)
        {
            for (int y = 0; buf[i][y]; y++)
            {
                std::cout << (char)std::toupper(buf[i][y]);
            }
        }
    }
    std::cout << std::endl;
}
