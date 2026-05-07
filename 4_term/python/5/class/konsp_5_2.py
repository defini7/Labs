class BankAccount:
    def __init__(self, initial_balance=0):
        self.__balance = initial_balance
    
    def deposit(self, amount):
        if amount > 0:
            self.__balance += amount
            print(f"Пополнение на сумму {amount} руб. Успешно выполнено.")
        else:
            print("Ошибка: Сумма пополнения должна быть положительной.")
    
    def withdraw(self, amount):
        if amount > 0:
            if amount <= self.__balance:
                self.__balance -= amount
                print(f"Снятие {amount} руб. Успешно выполнено.")
            else:
                print(f"Ошибка: Недостаточно средств. Доступно: {self.__balance} руб.")
        else:
            print("Ошибка: Сумма снятия должна быть положительной.")
    
    def get_balance(self):
        print(f"Текущий баланс: {self.__balance} руб.")
        return self.__balance
    