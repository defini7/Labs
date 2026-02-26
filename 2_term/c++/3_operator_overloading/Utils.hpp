#pragma once

#define GetVar(var, msg, cond, is) \
    do \
    { \
        std::cout << msg << ": "; \
        is >> var; \
    } \
    while (cond);

int GetRandomInt(int, int);
bool IsLeapYear(int);
