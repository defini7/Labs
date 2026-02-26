with open('6_1.txt') as file:
    rows_count = int(file.readline())
    rows = map(int, file.readlines())

with open('6_2.txt') as file:
    cols_count = int(file.readline())
    cols = map(int, file.readlines())

with open('6_3.txt') as file:
    values = map(int, file.readlines())

mat = {}

for row, col, value in zip(rows, cols, values):
    mat[row, col] = value

vec = [i for i in range(rows_count)]
res = [0] * rows_count

for r in range(1, rows_count + 1):
    s = 0

    for k in range(cols_count):
        if (r, k+1) in mat:
            s += mat[r, k+1] * vec[k]

    res[r-1] = s

print(res)