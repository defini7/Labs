def rek(n, *args):
    total_args = len(args)
    
    if total_args == 0:
        print("Ошибка: не переданы коэффициенты и начальные значения")
        return None
    
    num_coeffs = total_args // 2
    
    if total_args % 2 != 0:
        print("Ошибка: должно быть четное количество аргументов (коэффициенты и начальные значения)")
        return None
    
    coeffs = list(args[:num_coeffs])
    initial_values = list(args[num_coeffs:])
    
    if n <= len(initial_values):
        return initial_values[n - 1]
    
    sequence = initial_values.copy()
    
    for i in range(len(initial_values), n):
        next_value = 0

        for j in range(num_coeffs):
            if i - j - 1 >= 0:
                next_value += coeffs[j] * sequence[i - j - 1]
            else:
                print("Ошибка: недостаточно начальных значений для вычисления a_" + n)
                return None
            
        sequence.append(next_value)
    
    return sequence[n - 1]


print("a_5 =", rek(5, 2, 3, 1, 2))
print("a_10 =", rek(10, 1, 1, 1, 1))
print("a_5 =", rek(5, 1, 1, 1))
print("a_4 =", rek(4, 1, 2, 3, 1, 1, 1))
