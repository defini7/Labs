#include "TextUtils.h"

bool IsPalindrome(const QString& text)
{
    for (int i = 0; i < text.length() / 2; i++)
    {
        if (text.at(i).toLower() != text.at(text.length() - i - 1).toLower())
            return false;
    }

    return true;
}

QVector<QString> SplitIntoWords(const QString& text)
{
    QVector<QString> words;

    int start = -1;
    int i = 0;

    bool parsingWord = false;

    for (QChar c : text)
    {
        if (c.isLetter())
        {
            if (!parsingWord)
            {
                start = i;
                parsingWord = true;
            }
        }
        else
        {
            if (parsingWord)
            {
                int charsCount = i - start;

                words.push_back(text.mid(start, charsCount));

                parsingWord = false;
                start = -1;
            }
        }

        i++;
    }

    if (start != -1)
        words.push_back(text.mid(start, i - start));

    return words;
}

QVector<QString> FindPalindromes(const QString& text)
{
    const QVector<QString> words = SplitIntoWords(text);
    QVector<QString> palindromes;

    for (const QString& word : words)
    {
        if (IsPalindrome(word))
            palindromes.push_back(word);
    }

    return palindromes;
}
