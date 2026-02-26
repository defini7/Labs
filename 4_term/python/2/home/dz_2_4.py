synonyms = {}

with open('4.txt', 'r', encoding='utf-8') as file:
    for line in file:
        lhs, rhs = map(lambda x: x.strip().lower(), line.split(' - '))

        if lhs in synonyms:
            synonyms[lhs].append(rhs)
        else:
            synonyms[lhs] = [rhs]

        if rhs in synonyms:
            synonyms[rhs].append(lhs)
        else:
            synonyms[rhs] = [lhs]

word = input('Слово: ')

with open('4.txt', 'a', encoding='utf-8') as file:
    file.write('\n')

    for syn in synonyms[word]:
        file.write(syn + ' ')
