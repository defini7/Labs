first = float(input('Первое число: '))
second = float(input('Второе число: '))

oper = input('Операция: ')

match oper:
    case '+': print(first + second)
    case '-': print(first - second)
    case '*': print(first * second)

    case '/':
        if second == 0:
            print('На ноль делить нельзя!')
        else:
            print(first / second)

    case _: print('Неверная операция')
