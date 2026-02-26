#include "Match.hpp"

Match::Match(const char* teamName1, const char* teamName2, const Date& date)
    : m_Teams({ teamName1, teamName2 }), m_Date(date)
{
    
}

void Match::SetDate(const Date& date)
{
    m_Date = date;
}

void Match::SetTeams(const char* teamName1, const char* teamName2)
{
    m_Teams.first = teamName1;
    m_Teams.second = teamName2;
}

Date Match::GetDate() const
{
    return m_Date;
}

std::pair<const char*, const char*> Match::GetTeams() const
{
    return m_Teams;
}