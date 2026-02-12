from random import random
from math import pi, cos, sin


t = int(input('Кол-во шагов T: '))

x, y, z = (0, 0, 0)

average_dist = 0
max_dist = float('-inf')

for i in range(t):
    radius = random()

    theta, phi = random() * pi, random() * 2 * pi

    x += radius * cos(theta) * cos(phi)
    y += radius * cos(theta) * sin(phi)
    z += radius * sin(theta)

    dist = (x * x + y * y + z * z) ** 0.5

    if dist > max_dist:
        max_dist = dist

    average_dist += dist/t

end_dist = (x * x + y * y + z * z) ** 0.5

print((end_dist, average_dist, max_dist))
