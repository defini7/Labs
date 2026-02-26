#include "Match.hpp"
#include "Utils.hpp"

Match::Match(const std::string_view team1, const std::string_view team2, const Date& time)
{
    Teams[0] = team1;
    Teams[1] = team2;

    Time = time;
}

Match& Match::operator=(const Match& rhs)
{
    Teams[0] = rhs.Teams[0];
    Teams[1] = rhs.Teams[1];

    Time = rhs.Time;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Match& match)
{
    os << "Date = " << match.Time << std::endl;

    os << "Team 1 = " << match.Teams[0] << std::endl;
    os << "Team 2 = " << match.Teams[1];

    return os;
}

std::istream& operator>>(std::istream& is, Match& match)
{
    for (int j = 0; j < 2; j++)
        GetVar(match.Teams[j], "Enter team name", false, is);

    GetVar(match.Time.Year, "Enter a year", match.Time.Year <= 0, is);
    GetVar(match.Time.Month, "Enter a month", match.Time.Month <= 0 || match.Time.Month > 12, is);

    bool isLeap = IsLeapYear(match.Time.Year);

    GetVar(match.Time.Day, "Enter a day",
           match.Time.Day <= 0 ||
           match.Time.Day > 31 ||
           match.Time.Month == 2 && match.Time.Day > (isLeap ? 29 : 28), is);

    return is;
}
