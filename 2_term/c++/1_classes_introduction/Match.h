#pragma once

#include <utility>

struct Date
{
    int year;
    int month;
    int day;
};

class Match
{
public:
    Match() = default;
    Match(const char* teamName1, const char* teamName2, const Date& date);
    
    void SetDate(const Date& date);
    void SetTeams(const char* teamName1, const char* teamName2);
    
    Date GetDate() const;
    std::pair<const char*, const char*> GetTeams() const;
    
private:
    Date m_Date;
    std::pair<const char*, const char*> m_Teams;
        
};