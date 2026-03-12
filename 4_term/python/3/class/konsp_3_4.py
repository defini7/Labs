def find_polynom_roots(a=1, b=2, c=1):
    try:
        a, b, c = int(a), int(b), int(c)
    except ValueError:
        return None

    if a == 0:
        try:
            return -b / c
        except ZeroDivisionError:
            return None
        
    d = b * b - 4 * a * c
    sqrt_d = d ** 0.5

    return ((-b + sqrt_d) / (2 * a), (-b - sqrt_d) / (2 * a))


print(find_polynom_roots(3, 5, 1))
