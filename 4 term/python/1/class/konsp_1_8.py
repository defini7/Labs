row1 = int(input('Строка 1: '))
col1 = int(input('Столбец 1: '))

row2 = int(input('Строка 2: '))
col2 = int(input('Столбец 2: '))

if (row1 < 1 or row1 > 8 or
        col1 < 1 or col1 > 8 or
        row2 < 1 or row2 > 8 or
        col2 < 1 or col2 > 8):
    print('Одно из введеных значений меньше 1 или больше 8')
else:
    if row1 == row2 or col1 == col2:
        print('YES')
    else:
        print('NO')

