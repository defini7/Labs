#include "League.hpp"
#include "Utils.hpp"

#include <filesystem>

int main()
{
    /*Date d(20, 10, 2007);

    std::cout << ++d << std::endl;
    std::cout << d++ << std::endl;
    std::cout << --d << std::endl;
    std::cout << d-- << std::endl;

    std::cout << (d += Date(10, 20, 30)) << std::endl;
    std::cout << (d -= Date(24, 20, 10)) << std::endl;*/

    int i = 0;

    while (true)
    {
        std::string path = "./matches" + std::to_string(i) + ".txt";

        if (!std::filesystem::exists(path))
            break;

        League l;
        l.Load(path);
        
        std::cout << i + 1 << ':' << std::endl << l << std::endl;

        i++;
    }

    std::cout << std::endl;

    char c;

    do
    {
        League league;

        league.Create();
        league.QuickSort();

        std::cout << std::endl << league << std::endl;
        league.Save("matches" + std::to_string(i++) + ".txt");

        GetVar(c, "Would you like to start from the beginning? (y/n)",
               c != 'y' && c != 'n' && c != 'Y' && c != 'N', std::cin);
    }
    while (c == 'y' || c == 'Y');
}
