#include "League.hpp"

std::ostream& operator<<(std::ostream& os, const League& league)
{
    os << "League name = " << league.m_Title << std::endl;
    os << "Number of matches = " << league.m_MatchesCount << std::endl << std::endl;

    for (size_t i = 0; i < league.m_MatchesCount; i++)
    {
        Match& match = league.m_Matches[i];

        os << "Match " << i + 1 << std::endl;
        os << match << std::endl << std::endl;
    }

    return os;
}

std::istream& operator>>(std::istream& is, League& league)
{
    GetVar(league.m_Title, "Enter league title", false, is);

    for (size_t i = 0; i < league.m_MatchesCount; i++)
        is >> league.m_Matches[i];

    return is;
}

League::League(const League& rhs)
{
    operator=(rhs);
}

League::~League()
{
    if (m_Matches)
        delete[] m_Matches;
}

League& League::operator=(const League& rhs)
{
    if (m_Matches)
        delete[] m_Matches;

    m_MatchesCount = rhs.m_MatchesCount;
    m_Title = rhs.m_Title;

    m_Matches = new Match[m_MatchesCount];

    for (size_t i = 0; i < m_MatchesCount; i++)
        m_Matches[i] = rhs.m_Matches[i];

    return *this;
}

void League::Create()
{
    GetVar(m_MatchesCount, "Enter a number of matches", m_MatchesCount <= 0, std::cin);

    m_Matches = new Match[m_MatchesCount];

    char c;
    GetVar(c, "Would you like to generate the matches randomly? (y/n)",
           c != 'y' && c != 'n' && c != 'Y' && c != 'N', std::cin);

    if (c == 'y' || c == 'Y')
        FillRandomly();
    else
        operator>>(std::cin, *this);
}

void League::FillRandomly()
{
    size_t teamIndecies[2];
    int minYear, maxYear;

    GetVar(minYear, "Enter a minimal year", minYear <= 0, std::cin);
    GetVar(maxYear, "Enter a maximum year", maxYear <= 0 || maxYear < minYear, std::cin);

    const std::string* teams;

    if (GetRandomInt(0, s_Count - 1) == 0)
    {
        teams = s_EPL;
        m_Title = "EPL";
    }
    else
    {
        teams = s_LaLiga;
        m_Title = "LaLiga";
    }

    for (size_t i = 0; i < m_MatchesCount; i++)
    {
        Match& match = m_Matches[i];

        match.Time.Year = GetRandomInt(minYear, maxYear);
        match.Time.Month = GetRandomInt(1, 12);

        match.Time.Day =
            match.Time.Month == 2 ?
            GetRandomInt(1, 29) :
            GetRandomInt(1, 31);

        teamIndecies[0] = GetRandomInt(0, s_TeamsCount - 1);

        do teamIndecies[1] = GetRandomInt(0, s_TeamsCount - 1);
        while (teamIndecies[0] == teamIndecies[1]);

        for (int i = 0; i < 2; i++)
            match.Teams[i] = teams[teamIndecies[i]];
    }
}

void League::InsertionSort()
{
    for (size_t i = 1; i < m_MatchesCount; i++)
    {
        for (size_t j = i; j > 0 && m_Matches[j].Time < m_Matches[j - 1].Time; j--)
            std::swap(m_Matches[j], m_Matches[j - 1]);
    }
}

void League::QuickSort()
{
    QuickSortImpl(0, m_MatchesCount - 1);
}

void League::QuickSortImpl(size_t start, size_t end)
{
    if (start >= end)
        return;

    Date& pivot = m_Matches[start].Time;

    size_t i = start - 1;
    size_t j = end + 1;

    while (true)
    {
        do i++; while (m_Matches[i].Time < pivot);
        do j--; while (m_Matches[j].Time > pivot);

        if (i >= j)
            break;

        std::swap(m_Matches[i], m_Matches[j]);
    }

    QuickSortImpl(start, j);
    QuickSortImpl(j + 1, end);
}

const std::string League::s_EPL[League::s_TeamsCount] =
{
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

const std::string League::s_LaLiga[League::s_TeamsCount] =
{
    "Barcelona",
    "Real Madrid",
    "Atletico Madrid",
    "Athletic Club",
    "Villareal",
    "Rayo Vallecano",
    "Mallorca",
    "Real Betis",
    "Osasuna",
    "Girona",
    "Real Sociedad",
    "Sevilla",
    "Getafe",
    "Celta Vigo",
    "Espanyol",
    "Leganes",
    "Las Palmas",
    "Valencia",
    "Alaves",
    "Real Valladolid"
};
