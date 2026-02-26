from random import uniform
from math import pi, cos, sin


x = float(input('X центра: '))
y = float(input('Y центра: '))

radius = float(input('Радиус: '))

n = int(input('Количество точек: '))

a_x = int(input('A_x: '))
a_y = int(input('A_y: '))

min_dist = float('+inf')
min_coords = []

for i in range(n):
    angle = uniform(0, 2 * pi)

    # Точка на окружности
    x, y = cos(angle) * radius + x, sin(angle) * radius + y

    dist_to_a = ((x - a_x) ** 2 + (y - a_y) ** 2) ** 0.5

    if dist_to_a < min_dist:
        min_dist = dist_to_a
        min_coords = [(x, y)]
    elif dist_to_a == min_dist:
        min_coords += [dist_to_a]

print(f'Точки: {min_coords}, расстояние: {min_dist}')
