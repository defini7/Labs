from collections import deque
import sys


DIRECTIONS = [(-1, 0), (1, 0), (0, -1), (0, 1)]


def read_labyrinth(filename):
    try:
        with open(filename, "r", encoding="utf-8") as f:
            lines = [line.rstrip("\n") for line in f.readlines()]
    except FileNotFoundError:
        print(f"Ошибка: Файл {filename} не найден!")
        sys.exit(1)
    except Exception as e:
        print(f"Ошибка при чтении файла: {e}")
        sys.exit(1)
    
    if not lines:
        print("Ошибка: Файл пуст!")
        sys.exit(1)
    
    N = len(lines)
    M = len(lines[0]) if N > 0 else 0
    
    for i, line in enumerate(lines):
        if len(line) != M:
            print(f"Ошибка: Строка {i+1} имеет длину {len(line)}, ожидается {M}")
            sys.exit(1)
    
    labyrinth = []
    start = None
    finish = None
    
    for i, line in enumerate(lines):
        row = []
        for j, ch in enumerate(line.upper()):
            if ch not in "SFWO":
                print(f"Ошибка: В строке {i+1}, столбце {j+1} найден недопустимый символ {ch}")
                sys.exit(1)
            
            if ch == "S":
                if start is not None:
                    print(f"Ошибка: Найдено несколько входов! Первый в ({start[0]+1},{start[1]+1}), второй в ({i+1},{j+1})")
                    sys.exit(1)
                start = (i, j)
            elif ch == "F":
                if finish is not None:
                    print(f"Ошибка: Найдено несколько выходов! Первый в ({finish[0]+1},{finish[1]+1}), второй в ({i+1},{j+1})")
                    sys.exit(1)
                finish = (i, j)
            
            row.append(ch)

        labyrinth.append(row)
    
    if start is None:
        print("Ошибка: В лабиринте отсутствует вход!")
        sys.exit(1)
    
    if finish is None:
        print("Ошибка: В лабиринте отсутствует выход!")
        sys.exit(1)
    
    return labyrinth, N, M, start, finish


def bfs_find_path(labyrinth, N, M, start, finish):
    queue = deque() # для dfs меняем на стэк
    queue.append((start, [start]))
    
    visited = [[False] * M for _ in range(N)]
    visited[start[0]][start[1]] = True
    
    while queue:
        (x, y), path = queue.popleft()
        
        if (x, y) == finish:
            return path
        
        for dx, dy in DIRECTIONS:
            nx, ny = x + dx, y + dy
            
            if 0 <= nx < N and 0 <= ny < M:
                if not visited[nx][ny] and labyrinth[nx][ny] != "W":
                    visited[nx][ny] = True
                    queue.append(((nx, ny), path + [(nx, ny)]))
    
    return None


def mark_path_on_labyrinth(labyrinth, path, start, finish):
    result = [row[:] for row in labyrinth]
    
    for x, y in path:
        if (x, y) != start and (x, y) != finish:
            result[x][y] = "*"
    
    return result


def save_result(filename, labyrinth, path, start, finish):
    with open(filename, "w", encoding="utf-8") as f:
        if path is None:
            f.write("Из лабиринта невозможно выбраться.\n")
            f.write("\nИсходный лабиринт:\n")

            for row in labyrinth:
                f.write("".join(row) + "\n")
        else:
            f.write(f"Длина пути: {len(path)} шагов\n")
            f.write(f"Маршрут: {path[0]} -> ... -> {path[-1]}\n\n")
            
            f.write("Обозначения:\n")
            f.write("  S - старт\n")
            f.write("  F - финиш\n")
            f.write("  W - стена\n")
            f.write("  O - проход\n")
            f.write("  * - маршрут\n\n")
            
            marked = mark_path_on_labyrinth(labyrinth, path, start, finish)
            
            M = len(labyrinth[0])

            f.write("┌" + "───" * M + "┐\n")

            for row in marked:
                f.write("│")
                for cell in row:
                    f.write(f" {cell} ")
                f.write("│\n")

            f.write("└" + "───" * M + "┘\n")
            
            f.write("\nКоординаты пути:\n")

            for i, (x, y) in enumerate(path):
                f.write(f"  {i+1}. ({x+1}, {y+1})\n")


def print_labyrinth(labyrinth, path=None, start=None, finish=None):
    if path and start and finish:
        marked = mark_path_on_labyrinth(labyrinth, path, start, finish)
        display = marked
    else:
        display = labyrinth
    
    M = len(labyrinth[0])
    print("┌" + "───" * M + "┐")
    for row in display:
        print("│", end="")
        for cell in row:
            print(f" {cell} ", end="")
        print("│")
    print("└" + "───" * M + "┘")


input_file = input("Введите имя файла с лабиринтом: ").strip()

labyrinth, N, M, start, finish = read_labyrinth(input_file)

print(f"\nРазмер лабиринта: {N} x {M}")
print(f"Вход S: ({start[0]+1}, {start[1]+1})")
print(f"Выход F: ({finish[0]+1}, {finish[1]+1})")

print("\nИсходный лабиринт:")
print_labyrinth(labyrinth)

path = bfs_find_path(labyrinth, N, M, start, finish)

if path:
    print(f"Длина пути: {len(path)}")
    
    print("\nЛабиринт с отмеченным маршрутом:")
    print_labyrinth(labyrinth, path, start, finish)
else:
    print("Из лабиринта невозможно выбраться.")


save_result("out_3.txt", labyrinth, path, start, finish)
