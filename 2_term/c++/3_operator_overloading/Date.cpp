#include "Date.hpp"
#include "Utils.hpp"

#include <iomanip>

Date::Date(int day, int month, int year)
    : Day(day), Month(month), Year(year)
{

}

Date& Date::operator=(const Date& rhs)
{
    Year = rhs.Year;
    Month = rhs.Month;
    Day = rhs.Day;

    return *this;
}

int Date::ToInt() const
{
    return Year * 10000 + Month * 100 + Day;
}

bool Date::operator<(const Date& rhs)
{
    return ToInt() < rhs.ToInt();
}

bool Date::operator>(const Date& rhs)
{
    return ToInt() > rhs.ToInt();
}

Date& Date::operator++()
{
    Day++;

    if (Day > 31 || (Month == 2 && Day > (IsLeapYear(Year) ? 29 : 28)))
    {
        Day = 1;
        Month++;
    }

    if (Month > 12)
    {
        Year++;
        Month = 1;
    }

    return *this;
}

Date Date::operator++(int)
{
    Date date = *this;
    operator++();

    return date;
}

Date& Date::operator--()
{
    Day--;

    if (Day < 0)
    {
        Month--;
        
        if (Month == 2)
            Day = IsLeapYear(Year) ? 29 : 28;
        else
            Day = 31;
    }

    if (Month < 0)
    {
        Year--;
        Month = 12;
    }

    return *this;
}

Date Date::operator--(int)
{
    Date date = *this;
    operator--();

    return date;
}

Date& Date::operator+=(const Date& date)
{
    Year += date.Year;
    Day += date.Day;

    int februaryDays = (IsLeapYear(Year) ? 29 : 28);

    while (Day > 31 || (Month == 2 && Day > februaryDays))
    {
        Day -= (Month == 2) ? februaryDays : 31;
        Month++;
    }

    Month += date.Month;

    while (Month > 12)
    {
        Year++;
        Month -= 12;
    }

    return *this;
}

Date& Date::operator-=(const Date& date)
{
    Year -= date.Year;
    Day -= date.Day;

    int februaryDays = (IsLeapYear(Year) ? 29 : 28);

    while (Day <= 0)
    {
        Day += (Month == 2) ? februaryDays : 31;
        Month--;
    }

    Month -= date.Month;

    while (Month <= 0)
    {
        Year--;
        Month += 12;
    }

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << std::setfill('0') <<
        std::setw(2) << date.Day << '.' <<
        std::setw(2) << date.Month << '.' <<
        std::setw(4) << date.Year;

    return os;
}

std::istream& operator>>(std::istream& is, Date& date)
{
    is >> date.Day >> date.Month >> date.Year;
    return is;
}
