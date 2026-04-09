import re
import sys


def extract_code_blocks(filename):
    try:
        with open(filename, "r", encoding="utf-8") as f:
            content = f.read()
    except FileNotFoundError:
        print(f"Ошибка: Файл {filename} не найден!")
        sys.exit(1)
    except Exception as e:
        print(f"Ошибка при чтении файла: {e}")
        sys.exit(1)
    
    pattern = r"begin code\s*\n(.*?)\n\s*end code"
    blocks = re.findall(pattern, content, re.DOTALL | re.IGNORECASE)
    
    blocks = [block.strip() for block in blocks]
    
    return blocks


def execute_code_block(block, block_number):
    print(f"\nБлок #{block_number}")
    print(block)
    
    globals_dict = {}
    
    try:
        exec(block, globals_dict)
        return True
    except SyntaxError as e:
        print(f"\nСинтаксическая ошибка в строке {e.lineno}: {e.msg}")
        return False
    except Exception as e:
        print(f"\nОшибка выполнения: {type(e).__name__}: {e}")
        return False


filename = input("\nВведите имя файла: ").strip()

blocks = extract_code_blocks(filename)

if not blocks:
    print("В файле не найдено ни одного блока кода!")
    sys.exit(1)

print(f"Найдено блоков: {len(blocks)}")

for i, block in enumerate(blocks, 1):
    print(f"\nБлок #{i}")
    print(block)

if len(blocks) > 1:
    target_block = blocks[1]
else:
    target_block = blocks[0]

success = execute_code_block(target_block, 2)

while not success:    
    choice = input("\nХотите исправить код? (да/нет/показать код): ").strip().lower()
    
    if choice in ("нет", "no", "n"):
        print("\nПрограмма завершена.")
        break
    elif choice in ("показать код", "show"):
        print("\nТекущий код:")
        print(target_block)
        continue
    elif choice in ("да", "yes", "y"):
        print("\nВведите исправленный код (для завершения ввода введите END на отдельной строке):")

        lines = []

        while True:
            line = input()

            if line.strip() == "END":
                break

            lines.append(line)

        target_block = "\n".join(lines)

        print("\nИсправленный код:")
        print(target_block)
        
        success = execute_code_block(target_block, 2)
    else:
        print("Неизвестная команда. Попробуйте: да, нет, показать код")
