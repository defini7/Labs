dists = {}

max_dist = float('-inf')
points = []

with open('3.txt', 'r') as file:
    for line in file:
        line = line.rstrip()

        num_start = line.find(' ') + 1
        num_end = line.find(' ', num_start)

        num = int(line[num_start:num_end])

        dists[num] = 0
        prev_point = None

        for pair in line[num_end+1:].split(';'):
            x, y = map(int, pair.split(','))

            if prev_point is not None:
                prev_x, prev_y = prev_point

                dist = ((prev_x - x) ** 2 + (prev_y - y) ** 2) ** 0.5
                dists[num] += dist

                if dist > max_dist:
                    points = [prev_point, (x, y)]
                    max_dist = dist

            prev_point = (x, y)

print('Расстояния:', dists)
print(f'Самый длинный участок: {max_dist}. Начало: {points[0]}. Конец: {points[1]}') # ??????
