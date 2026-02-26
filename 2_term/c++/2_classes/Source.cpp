#include <iostream>

#include "Match.hpp"

int main()
{
    Match match1;
    Match match2("Barcelona", "BVB Dortmund", { 2025, 4, 9 });

    PrintMatch(match2);

    char answer;

    std::cout << "Would you like to generate values randomly (y/n)? ";
    std::cin >> answer;

    if (tolower(answer) == 'y')
    {
        int minYear, maxYear;

        std::cout << "Enter minimal and maximum years: ";
        std::cin >> minYear >> maxYear;

        match1.FillRandomly(minYear, maxYear);
    }
    else
        match1.FillFromStdin();

    PrintMatch(match1);

    std::cout << "Would you like to generate values randomly (y/n)? ";
    std::cin >> answer;

    size_t matchesCount;

    Match* matches =
        tolower(answer) == 'y' ?
        FillMatchesRandomly(matchesCount) :
        FillMatchesFromStdin(matchesCount);

    PrintMatches(matches, matchesCount);

    delete[] matches;
}
