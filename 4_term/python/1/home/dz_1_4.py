from random import random


succeeded = 0
TOTAL_EXPERIMENTS = 100000000

for experiment in range(TOTAL_EXPERIMENTS):
    x, y = random(), random()

    if x * x + y * y <= 1:
        succeeded += 1

print('Pi =', 4 * succeeded / TOTAL_EXPERIMENTS)
