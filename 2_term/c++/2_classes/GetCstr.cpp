#include "GetCstr.hpp"

#include <iostream>
#include <climits>

void FreeCharEntry(CharEntry* entry)
{
    while (entry)
    {
        CharEntry* next = entry->next;
        delete entry;
        entry = next;
    }
}

char* GetCstr(size_t* length)
{
    CharEntry* head = new CharEntry;
    head->value = std::cin.get();
    head->next = nullptr;

    if (std::cin.eof())
    {
        delete head;
        return nullptr;
    }

    if (head->value == '\n' || head->value == '\r')
        head->value = std::cin.get();

    CharEntry* entry;
    entry = head;

    size_t charsRead = 1;
    
    while (!std::cin.eof() && entry->value != '\n' && entry->value != '\r')
    {
        CharEntry* newEntry = new CharEntry;

        newEntry->value = std::cin.get();
        newEntry->next = nullptr;

        entry->next = newEntry;
        entry = newEntry;

        charsRead++;

        if (charsRead > SIZE_MAX)
        {
            FreeCharEntry(head);
            return nullptr;
        }
    }

    char* output = new char[charsRead];
    entry = head;

    for (size_t i = 0; i < charsRead; i++)
    {
        output[i] = entry->value;
        CharEntry* next = entry->next;
        delete entry;
        entry = next;
    }

    output[charsRead - 1] = '\0';

    if (length)
        *length = charsRead - 1;

    return output;
}
