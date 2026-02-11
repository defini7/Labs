n1 = input('Число 1: ')

if not n1.isdigit():
    print('Введено не число')
    exit(1)

n2 = input('Число 2: ')

if not n2.isdigit():
    print('Введено не число')
    exit(1)

n3 = input('Число 3: ')

if not n3.isdigit():
    print('Введено не число')
    exit(1)

if int(n1) - int(n2) == int(n2) - int(n3):
    print('Числа составляют арифметическую прогрессию')
else:
    print('Числа не составляют арифметическую прогрессию')