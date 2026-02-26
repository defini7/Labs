#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>

#include "Match.hpp"
#include "GetCstr.hpp"

#define GET_VAR(value, msg, cond) do { std::cout << msg << ": "; std::cin >> value; } while (cond)

int GetRandomInt(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

bool IsLeapYear(int year)
{
    return year % 400 == 0 || year % 4 == 0 && year % 100 != 0;
}

void PrintMatch(const Match& match)
{
    Date date = match.GetDate();

    const char* team1 = match.GetTeam(0);
    const char* team2 = match.GetTeam(1);

    std::cout << "Date: " << std::setw(2) << std::setfill('0') << date.day << "." << std::setw(2) << std::setfill('0') << date.month << "." << date.year << std::endl;
    std::cout << "Teams: " << team1 << ", " << team2 << std::endl;
}

Match* FillMatchesFromStdin(size_t& count)
{
    std::cout << "How many matches would you like to enter? ";
    std::cin >> count;

    Match* matches = new Match[count];

    for (size_t i = 0; i < count; i++)
        matches[i].FillFromStdin();

    return matches;
}

Match* FillMatchesRandomly(size_t& count)
{
    std::cout << "How many matches would you like to generate? ";
    std::cin >> count;

    int minYear, maxYear;

    std::cout << "Enter minimal and maximum years: ";
    std::cin >> minYear >> maxYear;

    Match* matches = new Match[count];

    for (size_t i = 0; i < count; i++)
        matches[i].FillRandomly(minYear, maxYear);

    return matches;
}

void PrintMatches(const Match* matches, size_t count)
{
    for (size_t i = 0; i < count; i++)
        PrintMatch(matches[i]);
}

Match::Match()
{
    m_Teams[0] = nullptr;
    m_Teams[1] = nullptr;
}

Match::Match(const char* team1, const char* team2, const Date& date)
    : m_Date(date)
{
    SetTeams(team1, team2);
}

Match::~Match()
{
    delete m_Teams[0];
    delete m_Teams[1];
}

void Match::FillRandomly(int minYear, int maxYear)
{
    static const char* s_Teams[] = {
        "Liverpool",
        "Arsenal",
        "Nottingham Forest",
        "Chelsea",
        "Manchester City",
        "Newcastle United",
        "AFC Bournemouth",
        "Brighton & Hove Albion",
        "Aston Villa",
        "Fulham",
        "Brentford",
        "Crystal Palace",
        "Manchester United",
        "Tottenham Hotspur",
        "Everton",
        "West Ham United",
        "Wolverhampton Wanderers",
        "Leicester City",
        "Ipswich Town",
        "Southampton"
    };

    static size_t s_TeamsCount = sizeof(s_Teams) / sizeof(s_Teams[0]);

    m_Date.year = GetRandomInt(minYear, maxYear);
    m_Date.month = GetRandomInt(1, 12);
    m_Date.day = m_Date.month == 2 ? GetRandomInt(1, 29) : GetRandomInt(1, 31);

    size_t indecies[2];

    do
    {
        for (int i = 0; i < 2; i++)
            indecies[i] = rand() % s_TeamsCount;
    }
    while (indecies[0] == indecies[1]);

    for (int i = 0; i < 2; i++)
    {
        const char* team = s_Teams[indecies[i]];
        size_t length = strlen(team);
        
        m_Teams[i] = new char[length + 1];
        strcpy(m_Teams[i], team);
    }
}

void Match::FillFromStdin()
{
    for (int j = 0; j < 2; j++)
    {
        std::cout << "Enter " << j + 1 << " team's name: ";
        m_Teams[j] = GetCstr();
    }

    GET_VAR(m_Date.year, "Enter the year", m_Date.year <= 0);
    GET_VAR(m_Date.month, "Enter the month", m_Date.month <= 0 || m_Date.month > 12);

    bool leap = IsLeapYear(m_Date.year);

    GET_VAR(m_Date.day, "Enter the day",
        m_Date.day <= 0 || m_Date.day > 31 || m_Date.month == 2 && m_Date.day > (leap ? 29 : 28));
}

void Match::SetTeams(const char* team1, const char* team2)
{
    m_Teams[0] = new char[strlen(team1) + 1];
    m_Teams[1] = new char[strlen(team2) + 1];

    strcpy(m_Teams[0], team1);
    strcpy(m_Teams[1], team2);
}

void Match::SetDate(const Date& date)
{
    m_Date = date;
}

const char* Match::GetTeam(size_t index) const
{
    if (index >= 2)
        return nullptr;

    return m_Teams[index];
}

Date Match::GetDate() const
{
    return m_Date;
}

