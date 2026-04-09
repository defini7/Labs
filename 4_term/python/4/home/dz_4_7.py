from fractions import Fraction
from itertools import product
import re
import sys


def generate_expressions(digits):
    if not digits:
        return {}
    
    n = len(digits)
    expressions = {}
    
    def build_expr(start, current_expr, current_val):
        if start == n:
            if current_expr:
                expressions[current_expr] = current_val

            return
        
        for end in range(start + 1, n + 1):
            num_str = digits[start:end]
            num = Fraction(int(num_str))
            
            if start == 0:
                build_expr(end, num_str, num)
            else:
                for op in "+-*/":
                    new_expr = current_expr + op + num_str
                    
                    if op == "+":
                        new_val = current_val + num
                    elif op == "-":
                        new_val = current_val - num
                    elif op == "*":
                        new_val = current_val * num
                    else:  # op == "/"
                        if num == 0:
                            continue
                        new_val = current_val / num
                    
                    build_expr(end, new_expr, new_val)
    
    build_expr(0, "", Fraction(0))

    return expressions


def generate_all_combinations(digits):
    n = len(digits)
    results = {}
    
    def split_numbers(pos, current_numbers):
        if pos == n:
            if current_numbers:
                num_count = len(current_numbers)
                if num_count == 1:
                    expr = str(current_numbers[0])
                    results[expr] = Fraction(current_numbers[0])
                else:
                    for ops in product("+-*/", repeat=num_count-1):
                        expr = str(current_numbers[0])

                        for i, op in enumerate(ops):
                            expr += op + str(current_numbers[i + 1])
                        
                        try:
                            val = evaluate_expression(expr)
                            results[expr] = val
                        except ZeroDivisionError:
                            continue

            return
        
        for end in range(pos + 1, n + 1):
            num = int(digits[pos:end])
            split_numbers(end, current_numbers + [num])
    
    split_numbers(0, [])
    return results


def evaluate_expression(expr):
    numbers = re.split(r"[+\-*/]", expr)
    numbers = [Fraction(int(n)) for n in numbers]
    ops = re.findall(r"[+\-*/]", expr)
    
    i = 0
    while i < len(ops):
        if ops[i] in ("*", "/"):
            if ops[i] == "*":
                numbers[i] *= numbers[i + 1]
            else:  # "/"
                if numbers[i + 1] == 0:
                    raise ZeroDivisionError
                numbers[i] /= numbers[i + 1]

            del numbers[i + 1]
            del ops[i]
        else:
            i += 1
    
    result = numbers[0]
    for i, op in enumerate(ops):
        if op == "+":
            result += numbers[i + 1]
        else:  # "-"
            result -= numbers[i + 1]
    
    return result


def find_representation(target, expressions):
    if isinstance(target, str):
        if "/" in target:
            a, b = target.split("/")
            target = Fraction(int(a), int(b))
        else:
            target = Fraction(int(target), 1)
    
    matches = []
    for expr, value in expressions.items():
        if value == target:
            matches.append(expr)
    
    return matches


def print_results(matches, target):
    if not matches:
        print(f"\nВыражений, равных {target}, не найдено.")
    else:
        print(f"\nНайдено {len(matches)} выражений, равных {target}:")

        for expr in matches:
            print(f"  {expr} = {target}")


digits = input("\nВведите строку цифр (например, 9999): ").strip()

if not digits.isdigit():
    print("Cтрока должна содержать только цифры!")
    sys.exit(1)

expressions = generate_all_combinations(digits)

print("\nПримеры выражений и их результаты:")

for i, (expr, val) in enumerate(list(expressions.items())):
    if val.denominator == 1:
        val_str = str(val.numerator)
    else:
        val_str = f"{val.numerator}/{val.denominator}"

    print(f"{i+1:2}. {expr} = {val_str}")


with open("expressions_dict.txt", "w", encoding="utf-8") as f:
    f.write(f"Словарь выражений для {digits}:\n")
    for expr, val in expressions.items():
        if val.denominator == 1:
            val_str = str(val.numerator)
        else:
            val_str = f"{val.numerator}/{val.denominator}"
        f.write(f"{expr}: {val_str}\n")

while True:
    query = input("\nВведите число для поиска (дробь в формате a/b или целое число, exit для выхода): ").strip()
    
    if query.lower() in ("exit", "quit", "q"):
        print("До свидания!")
        break
    
    if not query:
        continue
    
    try:
        if "/" in query:
            a, b = query.split("/")
            target = Fraction(int(a), int(b))
        else:
            target = Fraction(int(query), 1)
        
        matches = find_representation(target, expressions)
        
        if matches:
            print(f"\nРезультаты для {query}:")

            for expr in matches:
                print(f"  {expr} = {query}")
            
            if "/" in query:
                simple = Fraction(target.numerator, target.denominator)
                
                if simple != target:
                    print(f"\nСокращенная дробь: {target} = {simple}")
        else:
            print(f"\nВыражений, равных {query}, не найдено.")
            
    except (ValueError, ZeroDivisionError) as e:
        print(f"Неверный формат числа. Используйте формат a/b или целое число.")
