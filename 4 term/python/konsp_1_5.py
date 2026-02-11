number = input('Введите число ')

if len(number) != 3 or not number.isdecimal():
    print('Введено не трехзначное число')
    exit(1)

sum = 0
prod = 1

for i in range(3):
    n = int(number[i])

    sum += n
    prod *= n

print('Сумма', str(sum) + ', произведение', prod)
