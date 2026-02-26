#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TEAM_NAME_LENGTH 32

#define GET_VAR(ptr, msg, format, cond) do { printf("%s: ", msg); scanf(format, ptr); getchar(); } while (cond)

const char* TEAMS[] = {
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

const int TEAMS_COUNT = sizeof(TEAMS) / sizeof(TEAMS[0]);

typedef struct
{
    int year;
    int month;
    int day;
} Date;

typedef struct
{
    char teams[2][MAX_TEAM_NAME_LENGTH];
    Date date;
} Match;

int rand_int(int min, int max);

bool is_leap_year(int year);

void generate_matches_randomly(Match*, int);
void input_matches(Match*, int);
void print_matches(Match*, int);

Match* get_matches(int*);

int main()
{
    int matches_count;
    Match* matches = get_matches(&matches_count);

    print_matches(matches, matches_count);

    free(matches);
    return 0;
}

int rand_int(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

bool is_leap_year(int year)
{
    return year % 400 == 0 || year % 4 == 0 && year % 100 != 0;
}

void generate_matches_randomly(Match* matches, int length)
{
    if (!matches || length <= 0)
        return;

    srand(time(NULL));

    int indecies[2];
    int min_year, max_year;

    GET_VAR(&min_year, "Enter a minimal year", " %d", min_year <= 0);
    GET_VAR(&max_year, "Enter a maximum year", " %d", max_year <= 0 || max_year < min_year);

    for (int i = 0; i < length; i++)
    {
        Match* match = &matches[i];

        match->date.year = rand_int(min_year, max_year);
        match->date.month = rand_int(1, 12);
        match->date.day = match->date.month == 2 ? rand_int(1, 29) : rand_int(1, 31);

        do
        {
            for (int i = 0; i < 2; i++)
                indecies[i] = rand() % TEAMS_COUNT;
        }
        while (indecies[0] == indecies[1]);

        for (int i = 0; i < 2; i++)
            memcpy(match->teams[i], TEAMS[indecies[i]], strlen(TEAMS[indecies[i]]));
    }
}

void input_matches(Match* matches, int length)
{
    if (!matches || length <= 0)
        return;

    for (int i = 0; i < length; i++)
    {
        Match* match = &matches[i];
        
        for (int j = 0; j < 2; j++)
        {
            printf("Enter %d team's name (max %d chars): ", j + 1, MAX_TEAM_NAME_LENGTH);
            fgets(match->teams[j], MAX_TEAM_NAME_LENGTH, stdin);
            match->teams[j][strcspn(match->teams[j], "\n")] = '\0';
        }

        GET_VAR(&match->date.year, "Enter the year", "%d", match->date.year <= 0);
        GET_VAR(&match->date.month, "Enter the month", "%d", match->date.month <= 0 || match->date.month > 12);

        bool leap = is_leap_year(match->date.year);

        GET_VAR(&match->date.day, "Enter the day", "%d",
            match->date.day <= 0 || match->date.day > 31 || match->date.month == 2 && match->date.day > (leap ? 29 : 28));
    }
}

void print_matches(Match* matches, int length)
{
    if (!matches || length <= 0)
        return;

    for (int i = 0; i < length; i++)
    {
        printf("Match %d:\n", i + 1);

        Match* match = &matches[i];

        printf("\tdate:\n");
        printf("\t\tyear: %d\n", match->date.year);
        printf("\t\tmongth: %d\n", match->date.month);
        printf("\t\tday: %d\n", match->date.day);

        for (int j = 0; j < 2; j++)
            printf("\tteam %d: %s\n", j + 1, match->teams[j]);

        putchar('\n');
    }
}

Match* get_matches(int* length)
{
    GET_VAR(length, "Enter the number of matches", "%d", *length <= 0);

    Match* matches = (Match*)calloc(*length, sizeof(Match));

    if (!matches)
    {
        fprintf(stderr, "Couldn't allocate memory for the matches");
        return NULL;
    }

    char c;
    GET_VAR(&c, "Would you like to generate the matches randomly? (y/n)", " %c", c != 'y' && c != 'n' && c != 'Y' && c != 'N');
    c = tolower(c);

    if (c == 'y')
        generate_matches_randomly(matches, *length);
    else
        input_matches(matches, *length);

    return matches;
}
