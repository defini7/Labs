number = input('Введите число ')

sum = 0
prod = 1

for i in range(3):
    n = float(number[i])

    sum += n
    prod *= n

print('Сумма', str(sum) + ', произведение', prod)
