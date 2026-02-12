from math import pi, sin


x = float(input('Введите точку: '))
n = int(input('Введите количество членов ряда: '))

# pi / 2 * sin(x) - 16 / pi * sum(k / (4*k*k - 1)**2 * sin(2*k*x))

series_sum_while = 0
series_sum_for = 0

for k in range(1, n):
    print(k)
    series_sum_for += k / (4 * k * k - 1) ** 2 * sin(2 * k * x)

k = 1

while k < n:
    series_sum_while += k / (4*k*k - 1) ** 2 * sin(2 * k * x)
    k += 1

series_sum_for = pi / 2 * sin(x) - 16 / pi * series_sum_for
series_sum_while = pi / 2 * sin(x) - 16 / pi * series_sum_while

print('Сумма через for:', series_sum_for)
print('Сумма через while:', series_sum_while)

y = x * sin(x)

print('Сумма непосредственно:', y)
print('Погрешность:', abs(y - series_sum_for))
