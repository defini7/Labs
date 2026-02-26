#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define INSERTION_SORT
//#define QUICK_SORT

#define GET_VAR(ptr, msg, format, cond) do { printf("%s: ", msg); scanf(format, ptr); getchar(); } while (cond)
#define ALLOCATE(type, length) (type*)calloc(length, sizeof(type))

#define LEAGUE_COUNT 2
#define LEAGUE_TEAMS_COUNT 20

const char* LEAGUE_EPL[LEAGUE_TEAMS_COUNT] = {
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

const char* LEAGUE_LALIGA[LEAGUE_TEAMS_COUNT] = {
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

typedef struct
{
    int year;
    int month;
    int day;
} Date;

typedef struct
{
    char* teams[2];
    Date date;
} Match;

typedef struct
{
    char* name;
    int matches_count;
    Match* matches;
} League;

// Представляет Date как int
int date_to_int(const Date*);

// Меняет местами значения переменных типа Match
void match_swap(Match*, Match*);

// Возвращает случайное значение типа int из отрезка
int int_rand(int, int);

// Проверяет, является ли год високосным
bool is_leap_year(int);

// Создает копию строки
char* string_from(const char*);

// Считывает строку с клавиатуры
void string_get(char*, int);

// Заполняет данные о лиге случайным образом
void league_fill_randomly(League*);

// Запрашивает данные о лиги с клавиатуры
void league_input(League*);

// Выводит данные о лиге в консоль
void league_print(const League*);

// Освобождает память под данные о лиге
void league_free(League*);

// Запрашивает с клавиатуры способ генерации данных и генерирует их
League* league_generate();

#ifdef INSERTION_SORT
void league_sort(League*);
#endif

#ifdef QUICK_SORT
void league_sort_impl(League*, int, int);
void league_sort(League*);
#endif

int main()
{
    char c;

    do
    {
        League* league = league_generate();

        league_sort(league);
        league_print(league);
        league_free(league);

        GET_VAR(&c, "Would you like to start from the beginning? (y/n)", " %c", c != 'y' && c != 'n' && c != 'Y' && c != 'N');
    } while (c == 'y' || c == 'Y');

    return 0;
}

int date_to_int(const Date* date)
{
    return date->year * 10000 + date->month * 100 + date->day;
}

void match_swap(Match* first, Match* second)
{
    Match temp = *first;
    *first = *second;
    *second = temp;
}

int int_rand(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

char* string_from(const char* str)
{
    int bytes_count = strlen(str) + 1;

    char* buffer = ALLOCATE(char, bytes_count);
    assert(buffer && "Couldn't allocate memory for a string");

    memcpy(buffer, str, bytes_count);
    return buffer;
}

bool is_leap_year(int year)
{
    return year % 400 == 0 || year % 4 == 0 && year % 100 != 0;
}

void string_get(char* ptr, int max_length)
{
    fgets(ptr, max_length, stdin);

    // Ищем символ перехода на новую строку и заменяем его на заверщающий 0
    ptr[strcspn(ptr, "\n")] = '\0';
}

void league_fill_randomly(League* league)
{
    srand(time(NULL));

    int team_indecies[2];
    int min_year, max_year;

    GET_VAR(&min_year, "Enter a minimal year", "%d", min_year <= 0);
    GET_VAR(&max_year, "Enter a maximum year", "%d", max_year <= 0 || max_year < min_year);

    // Randomly select a league

    const char** teams;

    if (int_rand(0, LEAGUE_COUNT - 1) == 0)
    {
        teams = LEAGUE_EPL;
        league->name = string_from("EPL");
    }
    else
    {
        teams = LEAGUE_LALIGA;
        league->name = string_from("La Liga");
    }

    for (int i = 0; i < league->matches_count; i++)
    {
        Match* match = &league->matches[i];

        match->date.year = int_rand(min_year, max_year);
        match->date.month = int_rand(1, 12);
        match->date.day = match->date.month == 2 ? int_rand(1, 29) : int_rand(1, 31);

        team_indecies[0] = int_rand(0, LEAGUE_TEAMS_COUNT - 1);

        do
        {
            team_indecies[1] = int_rand(0, LEAGUE_TEAMS_COUNT - 1);
        } while (team_indecies[0] == team_indecies[1]);

        for (int i = 0; i < 2; i++)
        {
            int bytes_count = strlen(teams[team_indecies[i]]) + 1;

            match->teams[i] = ALLOCATE(char, bytes_count);
            assert(match->teams[i] && "Couldn't allocate memory for a team");

            memcpy(match->teams[i], teams[team_indecies[i]], bytes_count);
        }
    }
}

void league_input(League* league)
{
    int name_length;

    GET_VAR(&name_length, "Enter the number of chars in a league name", "%d", name_length <= 0);

    league->name = ALLOCATE(char, name_length + 1);
    assert(league->name && "Couldn't allocate memory for a league name");

    printf("Enter the league's name: ");
    string_get(league->name, name_length + 1);

    for (int i = 0; i < league->matches_count; i++)
    {
        Match* match = &league->matches[i];

        for (int j = 0; j < 2; j++)
        {
            GET_VAR(&name_length, "Enter the number of chars in a team name", "%d", name_length <= 0);
            match->teams[j] = ALLOCATE(char, name_length + 1);

            printf("Enter the %d team's name: ", j + 1);
            string_get(match->teams[j], name_length + 1);
        }

        GET_VAR(&match->date.year, "Enter the year", "%d", match->date.year <= 0);
        GET_VAR(&match->date.month, "Enter the month", "%d", match->date.month <= 0 || match->date.month > 12);

        bool is_leap = is_leap_year(match->date.year);

        GET_VAR(&match->date.day, "Enter the day", "%d",
            match->date.day <= 0 || match->date.day > 31 || match->date.month == 2 && match->date.day > (is_leap ? 29 : 28));
    }
}

void league_print(const League* league)
{
    printf("\nLeague name: %s\n", league->name);
    printf("Number of matches: %d\n\n", league->matches_count);

    for (int i = 0; i < league->matches_count; i++)
    {
        Match* match = &league->matches[i];

        printf("Match %d:\n", i + 1);

        printf("\tDate: %d.%d.%d\n", match->date.day, match->date.month, match->date.year);

        printf("\tTeam 1: %s\n",   match->teams[0]);
        printf("\tTeam 2: %s\n\n", match->teams[1]);
    }
}

League* league_generate()
{
    League* league = (League*)malloc(sizeof(League));
    assert(league && "Couldn't allocate memory for a league");

    GET_VAR(&league->matches_count, "Enter a number of matches", "%d", league->matches_count <= 0);

    league->matches = ALLOCATE(Match, league->matches_count);
    assert(league->matches && "Couldn't allocate memory for the matches");

    char c;
    GET_VAR(&c, "Would you like to generate the matches randomly? (y/n)", " %c", c != 'y' && c != 'n' && c != 'Y' && c != 'N');

    if (c == 'y' || c == 'Y')
        league_fill_randomly(league);
    else
        league_input(league);

    return league;
}

void league_free(League* league)
{
    for (int i = 0; i < league->matches_count; i++)
    {
        free(league->matches[i].teams[0]);
        free(league->matches[i].teams[1]);
    }

    free(league->matches);
    free(league->name);

    free(league);
}

#ifdef INSERTION_SORT

void league_sort(League* league)
{
    for (int i = 1; i < league->matches_count; i++)
    {
        for (int j = i; j > 0 && date_to_int(&league->matches[j].date) < date_to_int(&league->matches[j - 1].date); j--)
            match_swap(league->matches + j, league->matches + j - 1);
    }
}

#endif

#ifdef QUICK_SORT

void league_sort_impl(League* league, int start, int end)
{
    if (start >= end)
        return;

    Date* pivot = &league->matches[start].date;

    int i = start - 1;
    int j = end + 1;

    while (1)
    {
        do i++; while (date_to_int(&league->matches[i].date) < date_to_int(pivot));
        do j--; while (date_to_int(&league->matches[j].date) > date_to_int(pivot));

        if (i >= j)
            break;

        match_swap(&league->matches[i], &league->matches[j]);
    }

    league_sort_impl(league, start, j);
    league_sort_impl(league, j + 1, end);
}

void league_sort(League* league)
{
    league_sort_impl(league, 0, league->matches_count - 1);
}

#endif
