#include "League.hpp"

int main()
{
    Date d(20, 10, 2007);

    std::cout << ++d << std::endl;
    std::cout << d++ << std::endl;
    std::cout << --d << std::endl;
    std::cout << d-- << std::endl;

    std::cout << (d += Date(10, 20, 30)) << std::endl;
    std::cout << (d -= Date(24, 20, 10)) << std::endl;

    //char c;

    /*do
    {
        League league;

        league.Create();
        league.QuickSort();

        std::cout << std::endl << league << std::endl;

        GetVar(c, "Would you like to start from the beginning? (y/n)",
               c != 'y' && c != 'n' && c != 'Y' && c != 'N', std::cin);
    }
    while (c == 'y' || c == 'Y');*/
}
