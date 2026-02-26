#pragma once

#include <ostream>
#include <istream>

/*  Assume that every month contains 31 days
    and Feb can contain 28 or 29 days */
class Date
{
public:
    Date(int day = 0, int month = 0, int year = 0);

    Date& operator=(const Date&);

    int ToInt() const;
    void FromInt(int time);

    bool operator<(const Date&);
    bool operator>(const Date&);

    Date& operator++();
    Date operator++(int);

    Date& operator--();
    Date operator--(int);

    Date& operator+=(const Date&);
    Date& operator-=(const Date&);

    friend std::ostream& operator<<(std::ostream&, const Date&);
    friend std::istream& operator>>(std::istream&, Date&);

public:
    int Day;
    int Month;
    int Year;

};
