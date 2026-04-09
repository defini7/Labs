import re
import sys


filename = input("\nВведите имя файла: ").strip()

try:
    with open(filename, "r", encoding="utf-8") as f:
        text = f.read()
except FileNotFoundError:
    print(f"Файл не найден!")
    
except Exception as e:
    print(f"Ошибка при чтении файла: {e}")
    sys.exit(1)

result_text = re.sub(r"p+m*a{2,}", "ххх", text)
print(result_text)

try:
    with open("out_6.txt", "w", encoding="utf-8") as f:
        f.write(result_text)
except Exception as e:
    print(f"Ошибка при сохранении файла: {e}")
