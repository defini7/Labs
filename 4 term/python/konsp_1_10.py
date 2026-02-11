a1 = int(input('a_1: '))
b1 = int(input('b_1: '))

if a1 > b1:
    print('Ошибка: a1 > b1')
    exit(1)

a2 = int(input('a_2: '))
b2 = int(input('b_2: '))

if a2 > b2:
    print('Ошибка: a2 > b2')
    exit(1)

# 3 7 1 5
# 1 9 5 7
# 1 10 5 8
# 10 20 15 60

if a1 <= a2 and b2 <= b1:
    print(a2, b2)
elif a2 <= a1 and b1 <= b2:
    print(a1, b1)
elif b1 >= a2:
    print(a1 if a1 >= a2 else a2, b1 if b1 <= b2 else b2)
else:
    print('Нет пересечения')
