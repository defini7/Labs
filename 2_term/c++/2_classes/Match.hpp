#pragma once

struct Date
{
    Date() = default;

    int year;
    int month;
    int day;
};

int GetRandomInt(int min, int max);
bool IsLeapYear(int year);

class Match
{
public:
    Match();
    Match(const char* team1, const char* team2, const Date& date);

    ~Match();

    void FillRandomly(int minYear, int maxYear);
    void FillFromStdin();

    void SetTeams(const char* team1, const char* team2);
    void SetDate(const Date& date);

    const char* GetTeam(size_t index) const;
    Date GetDate() const;

private:
    char* m_Teams[2];
    Date m_Date;

};

void PrintMatch(const Match& match);

Match* FillMatchesFromStdin(size_t& count);
Match* FillMatchesRandomly(size_t& count);

void PrintMatches(const Match* matches, size_t count);
