#include <iostream>
#include <cctype>

int main(int ac, char **av)
{

    if(ac == 1)
    {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return(0);
    }
    for (int i = 1; i < ac; ++i)
    {
        for (int j = 0; av[i][j] !='\0'; ++j)
        {
            unsigned char c = static_cast<unsigned char>(av[i][j]);
            std::cout << static_cast<char>(std::toupper(c));
        }
    }
    
    std::cout << std::endl;
    return(0);
}