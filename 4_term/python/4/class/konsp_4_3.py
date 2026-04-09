import re


def replace_numbers_with_increment_negative(text):
    def increment(match):
        num_str = match.group(0)
        if "." in num_str:
            num = float(num_str)
            return str(num + 2)
        else:
            num = int(num_str)
            return str(num + 2)
    
    result = re.sub(r"-?\d+(?:\.\d+)?", increment, text)
    return result


text = input("Введите строку: ")
result = replace_numbers_with_increment_negative(text)
print("Результат:", result)
