n = input('Целое число ')

if n.isdecimal():
    n = int(n)
    print(n - 1, n + 1)
else:
    print('Введено не целое число')
