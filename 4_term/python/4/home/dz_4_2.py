import random


def generate_matrix(N, M, min_val=0, max_val=9):
    return [[random.randint(min_val, max_val) for _ in range(M)] for _ in range(N)]


def find_max_sum_path(matrix, start, end):
    N = len(matrix)
    M = len(matrix[0])
    r1, c1 = start
    r2, c2 = end
    
    row_step = 1 if r2 >= r1 else -1
    col_step = 1 if c2 >= c1 else -1
    
    dp = [[-float("inf")] * M for _ in range(N)]
    prev = [[None] * M for _ in range(N)]
    
    dp[r1][c1] = matrix[r1][c1]
    
    for i in range(r1, r2 + row_step, row_step):
        for j in range(c1, c2 + col_step, col_step):
            if i == r1 and j == c1:
                continue
            
            candidates = []
            
            if i - row_step >= min(r1, r2) and i - row_step <= max(r1, r2):
                if dp[i - row_step][j] != -float("inf"):
                    candidates.append((dp[i - row_step][j], (i - row_step, j)))
            
            if j - col_step >= min(c1, c2) and j - col_step <= max(c1, c2):
                if dp[i][j - col_step] != -float("inf"):
                    candidates.append((dp[i][j - col_step], (i, j - col_step)))
            
            if candidates:
                max_val, prev_pos = max(candidates, key=lambda x: x[0])
                dp[i][j] = max_val + matrix[i][j]
                prev[i][j] = prev_pos
    
    if dp[r2][c2] == -float("inf"):
        return None, None
    
    path = []
    cur = (r2, c2)

    while cur != (r1, c1):
        path.append(cur)
        cur = prev[cur[0]][cur[1]]

    path.append((r1, c1))
    path.reverse()
    
    return path, dp[r2][c2]


def visualize_path_in_matrix(matrix, path, start, end):
    N = len(matrix)
    M = len(matrix[0])
    
    display = [[str(matrix[i][j]) for j in range(M)] for i in range(N)]

    for _, (r, c) in enumerate(path):
        if (r, c) == start or (r, c) == end:
            display[r][c] = f"+{display[r][c]}+"
        else:
            display[r][c] = f"*{display[r][c]}*"
    
    return display


def save_results_to_file(filename, matrix, path, max_sum, start, end):
    with open(filename, "w", encoding="utf-8") as f:
        f.write(f"Размер матрицы: {len(matrix)} x {len(matrix[0])}\n")
        f.write(f"Начальная точка: {start}\n")
        f.write(f"Конечная точка: {end}\n")
        f.write(f"Максимальная сумма маршрута: {max_sum}\n")
        
        if path:
            f.write(f"Длина маршрута: {len(path)} шагов\n")
            f.write(f"Маршрут: {" -> ".join([f"({r},{c})" for r, c in path])}\n")
        else:
            f.write("Маршрут не найден!\n")
        
        f.write("Обозначения:\n")
        f.write("  + - начальная или конечная точка маршрута\n")
        f.write("  * - промежуточная точка маршрута\n")
        
        if path:
            display = visualize_path_in_matrix(matrix, path, start, end)
            
            f.write("┌" + "─────" * len(matrix[0]) + "┐\n")
            for row in display:
                f.write("│")
                for cell in row:
                    f.write(f"{cell:^5}")
                f.write("│\n")
            f.write("└" + "─────" * len(matrix[0]) + "┘\n")
        else:
            f.write("┌" + "───" * len(matrix[0]) + "┐\n")
            for row in matrix:
                f.write("│")
                for cell in row:
                    f.write(f"{cell:^3}")
                f.write("│\n")
            f.write("└" + "───" * len(matrix[0]) + "┘\n")


def print_matrix_console(matrix, path=None, start=None, end=None):
    if path and start and end:
        display = visualize_path_in_matrix(matrix, path, start, end)
        for row in display:
            print(" ".join(f"{cell:^5}" for cell in row))
    else:
        for row in matrix:
            print(" ".join(f"{cell:^3}" for cell in row))


N = int(input("Введите количество строк N: "))
M = int(input("Введите количество столбцов M: "))

matrix = generate_matrix(N, M, 0, 9)

print("\nСгенерированная матрица:")
print_matrix_console(matrix)

print("\nВведите координаты начальной точки (индексы от 0 до N-1 и M-1):")
r1 = int(input("Строка: "))
c1 = int(input("Столбец: "))

print("\nВведите координаты конечной точки:")
r2 = int(input("Строка: "))
c2 = int(input("Столбец: "))

start = (r1, c1)
end = (r2, c2)

path, max_sum = find_max_sum_path(matrix, start, end)

if path:
    print(f"Максимальная сумма маршрута: {max_sum}")
    print(f"Маршрут: {" -> ".join([f"({r},{c})" for r, c in path])}")
    
    print("\nОбозначения: + - начало/конец, * - промежуточные точки")
    print_matrix_console(matrix, path, start, end)
else:
    print("Маршрут не найден!")

save_results_to_file("out_2.txt", matrix, path, max_sum, start, end)
