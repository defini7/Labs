import sys


def calculate_mixed_product(a, b, c):
    bc_x = b[1] * c[2] - b[2] * c[1]
    bc_y = b[2] * c[0] - b[0] * c[2]
    bc_z = b[0] * c[1] - b[1] * c[0]
    
    mixed_product = a[0] * bc_x + a[1] * bc_y + a[2] * bc_z
    
    return mixed_product


def print_formula(a, b, c, result):
    print("\nФормула смешанного произведения:")
    print(f"  a = ({a[0]}, {a[1]}, {a[2]})")
    print(f"  b = ({b[0]}, {b[1]}, {b[2]})")
    print(f"  c = ({c[0]}, {c[1]}, {c[2]})")

    print("\n  a · (b × c) =")
    print(f"  = a_x(b_y·c_z - b_z·c_y) + a_y(b_z·c_x - b_x·c_z) + a_z(b_x·c_y - b_y·c_x)")
    print(f"  = {a[0]}·({b[1]}·{c[2]} - {b[2]}·{c[1]}) + {a[1]}·({b[2]}·{c[0]} - {b[0]}·{c[2]}) + {a[2]}·({b[0]}·{c[1]} - {b[1]}·{c[0]})")
    print(f"  = {a[0]}·({b[1]*c[2]} - {b[2]*c[1]}) + {a[1]}·({b[2]*c[0]} - {b[0]*c[2]}) + {a[2]}·({b[0]*c[1]} - {b[1]*c[0]})")
    print(f"  = {a[0]}·{b[1]*c[2] - b[2]*c[1]} + {a[1]}·{b[2]*c[0] - b[0]*c[2]} + {a[2]}·{b[0]*c[1] - b[1]*c[0]}")
    print(f"  = {result}")


def parse_arguments():
    args = sys.argv[1:]  # пропускаем имя скрипта
    
    if not args:
        print("Ошибка: не указаны аргументы", file=sys.stderr)
        print_usage()
        sys.exit(1)
    
    if args[0] != "-v":
        print("Ошибка: первый аргумент должен быть -v", file=sys.stderr)
        print_usage()
        sys.exit(1)
    
    show_formula = False
    vector_args = []
    
    i = 1
    while i < len(args):
        if args[i] == "-h":
            show_formula = True
            i += 1
        else:
            vector_args.append(args[i])
            i += 1
    
    if len(vector_args) != 9:
        print(f"Ошибка: требуется 9 чисел, получено {len(vector_args)}", file=sys.stderr)
        print_usage()
        sys.exit(1)
    
    try:
        coords = [float(x) for x in vector_args]
    except ValueError as e:
        print(f"Ошибка: все координаты должны быть числами - {e}", file=sys.stderr)
        sys.exit(1)
    
    a = tuple(coords[0:3])
    b = tuple(coords[3:6])
    c = tuple(coords[6:9])
    
    return a, b, c, show_formula


def print_usage():
    """Выводит справку по использованию программы."""
    print("Использование:", file=sys.stderr)
    print(f"  {sys.argv[0]} -v x1 y1 z1 x2 y2 z2 x3 y3 z3 [-h]", file=sys.stderr)
    print("  -v  : флаг, после которого идут координаты трех векторов (9 чисел)", file=sys.stderr)
    print("  -h  : опциональный флаг для вывода формулы", file=sys.stderr)
    print("\nПримеры:", file=sys.stderr)
    print(f"  {sys.argv[0]} -v 1 2 3 4 5 6 7 8 9", file=sys.stderr)
    print(f"  {sys.argv[0]} -v 1 2 3 4 5 6 7 8 9 -h", file=sys.stderr)


def main():
    try:
        a, b, c, show_formula = parse_arguments()
    except SystemExit:
        raise
    except Exception as e:
        print(f"Ошибка при разборе аргументов: {e}", file=sys.stderr)
        sys.exit(1)
    
    result = calculate_mixed_product(a, b, c)
    
    print(f"Результат смешанного произведения: {result}")
    
    if show_formula:
        print_formula(a, b, c, result)


if __name__ == "__main__":
    main()
