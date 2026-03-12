def find_all_in_str(target, symbol):
    if len(target) == 0 or len(symbol) == 0:
        return []

    indecies = []
    i = -1

    while True:
        i = symbol.find(target, i + 1)

        if i == -1:
            break
        else:
            indecies.append(i)

    return indecies


print(find_all_in_str('a', 'bcadefgaygra'))
