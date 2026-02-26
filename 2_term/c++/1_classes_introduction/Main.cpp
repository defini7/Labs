#include <iostream>
#include <iomanip>

#include "Match.hpp"

void PrintMatch(const Match& match)
{
    Date date = match.GetDate();
    std::pair<const char*, const char*> teams = match.GetTeams();
    
    std::cout << "Date: " << std::setw(2) << std::setfill('0') << date.day << "." << std::setw(2) << std::setfill('0') << date.month << "." << date.year << std::endl;
    std::cout << "Teams: " << teams.first << ", " << teams.second << std::endl;
}

int main()
{
    Match match("Barcelona", "BVB", { 2025, 4, 5 });
    PrintMatch(match);
}