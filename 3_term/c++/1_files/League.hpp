#pragma once

#include "Match.hpp"

class League
{
public:
    League() = default;
    League(const League&);
    ~League();

    League& operator=(const League&);

    void Create();
    void FillRandomly();
    void InsertionSort();
    void QuickSort();

    bool Load(const std::string_view filename);
    bool Save(const std::string_view filename);

    friend std::ostream& operator<<(std::ostream&, const League&);
    friend std::istream& operator>>(std::istream&, League&);

public:
    static constexpr size_t s_Count = 2;
    static constexpr size_t s_TeamsCount = 20;

    static const std::string s_EPL[s_TeamsCount];
    static const std::string s_LaLiga[s_TeamsCount];

private:
    void QuickSortImpl(size_t start, size_t end);

private:
    Match* m_Matches = nullptr;
    size_t m_MatchesCount = 0;

    std::string m_Title;

};
