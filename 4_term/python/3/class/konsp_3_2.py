def get_jacts(m):
    divs = [1]

    for n in range(2, m // 2 + 1):
        if m % n == 0:
            divs.append(n)

    return divs


print(get_jacts(10))


