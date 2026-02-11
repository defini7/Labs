a = int(input('A: '))
b = int(input('B: '))

if a >= b:
    print('A >= B')
    exit(1)

max_sum = float('-inf')
num = 0

for n in range(a, b + 1):
    sum = n

    for d in range(1, n // 2 + 1):
        if n % d == 0:
            sum += d

    if sum > max_sum:
        max_sum = sum
        num = n

print('Сумма:', max_sum, 'число:', num)
