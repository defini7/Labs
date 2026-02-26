#pragma once

struct CharEntry
{
    char value;
    CharEntry* next;
};

void FreeCharEntry(CharEntry* entry);
char* GetCstr(size_t* length = nullptr);
