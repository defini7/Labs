#pragma once

#include <iostream>
#include <string>

#include "Date.hpp"

class Match
{
public:
    Match() = default;
    Match(const std::string_view team1, const std::string_view team2, const Date& date);

    Match& operator=(const Match&);

    friend std::ostream& operator<<(std::ostream&, const Match&);
    friend std::istream& operator>>(std::istream&, Match&);

public:
    std::string Teams[2];
    Date Time;

};
