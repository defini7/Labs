#include "Utils.hpp"

#include <random>

int GetRandomInt(int min, int max)
{
    static std::mt19937 s_Engine;
    std::uniform_int_distribution dist(min, max);
    return dist(s_Engine);
}

bool IsLeapYear(int year)
{
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}
