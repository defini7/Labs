a = float(input('a: '))
b = float(input('b: '))
c = float(input('c: '))
d = float(input('d: '))
e = float(input('e: '))
f = float(input('f: '))

"""
ax+by=e
cx+dy=f
"""

det = a * d - c * b
det_x = e * d - f * b
det_y = a * f - c * e

if det == 0:
    if det_x == 0 and det_y == 0:
        print('Решений бесконечно много')
    else:
        print('Решений нет')
else:
    x, y = det_x / det, det_y / det

    print('Решение:', x, y)
