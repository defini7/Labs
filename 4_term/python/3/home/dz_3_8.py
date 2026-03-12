heights = {}

with open("8.txt") as f:
    for line in f.readlines():
        idx, height = line.split()
        heights[int(idx)] = int(height)

if len(heights) < 3:
    raise RuntimeError("Замок слишком узкий для удержания воды")

heights = { idx: heights[idx] for idx in sorted(heights.keys()) }

n = len(heights)

max_left = [0] * n
max_right = [0] * n

max_left[0] = heights[0]

for i in range(1, n):
    max_left[i] = max(max_left[i - 1], heights[i])

max_right[n - 1] = heights[n - 1]

for i in range(n - 2, -1, -1):
    max_right[i] = max(max_right[i + 1], heights[i])

total = 0

for i in range(n):
    potential = min(max_left[i], max_right[i]) - heights[i]

    if potential > 0:
        total += potential

print(total)
