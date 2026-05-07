class InsufficientFundsError(Exception):
    pass

class NegativeAmountError(Exception):
    pass

class AccountNotFoundError(Exception):
    pass


class Account:
    def __init__(self, account_number, owner_name, initial_balance=0):
        self._account_number = account_number
        self._owner_name = owner_name
        self.__balance = initial_balance
    
    @property
    def account_number(self):
        return self._account_number
    
    @property
    def owner_name(self):
        return self._owner_name
    
    @property
    def balance(self):
        return self.__balance
    
    def deposit(self, amount):
        if amount < 0:
            raise NegativeAmountError("Сумма пополнения не может быть отрицательной")
        if amount == 0:
            raise NegativeAmountError("Сумма пополнения должна быть больше нуля")
        
        self.__balance += amount
        print(f"Счет {self._account_number}: Пополнение на {amount} руб. Баланс: {self.__balance} руб.")
    
    def withdraw(self, amount):
        if amount < 0:
            raise NegativeAmountError("Сумма снятия не может быть отрицательной")
        if amount == 0:
            raise NegativeAmountError("Сумма снятия должна быть больше нуля")
        if amount > self.__balance:
            raise InsufficientFundsError(f"Недостаточно средств. Доступно: {self.__balance} руб., запрошено: {amount} руб.")
        
        self.__balance -= amount
        print(f"Счет {self._account_number}: Снятие {amount} руб. Баланс: {self.__balance} руб.")
        return amount
    
    def apply_monthly_fee(self):
        pass
    
    def __str__(self):
        return f"Account({self._account_number}, {self._owner_name}, баланс: {self.__balance} руб.)"


class SavingsAccount(Account):
    def __init__(self, account_number, owner_name, initial_balance=0, interest_rate=0.05):
        super().__init__(account_number, owner_name, initial_balance)
        self._interest_rate = interest_rate
    
    def apply_interest(self):
        monthly_interest = self.balance * (self._interest_rate / 12)
        self.deposit(monthly_interest)
        print(f"Счет {self.account_number}: Начислены проценты {monthly_interest:.2f} руб. по ставке {self._interest_rate*100}% годовых")
    
    def apply_monthly_fee(self):
        self.apply_interest()
    
    def __str__(self):
        return f"SavingsAccount({self.account_number}, {self.owner_name}, баланс: {self.balance:.2f} руб., ставка: {self._interest_rate*100}%)"


class CheckingAccount(Account):
    def __init__(self, account_number, owner_name, initial_balance=0, withdrawal_fee=30):
        super().__init__(account_number, owner_name, initial_balance)
        self._withdrawal_fee = withdrawal_fee
        self._free_withdrawals = 5
        self._withdrawal_count = 0
    
    def withdraw(self, amount):
        total_amount = amount + self._withdrawal_fee
        
        if self._withdrawal_count < self._free_withdrawals:
            total_amount = amount
            fee_info = " (бесплатно)"
        else:
            fee_info = f" (включая комиссию {self._withdrawal_fee} руб.)"
        
        print(f"Запрос на снятие {amount} руб.{fee_info}")
        super().withdraw(total_amount)
        self._withdrawal_count += 1
        print(f"Счет {self.account_number}: использовано снятий в этом месяце: {self._withdrawal_count}")
        return amount
    
    def reset_monthly_withdrawals(self):
        self._withdrawal_count = 0
        print(f"Счет {self.account_number}: счетчик снятий сброшен")
    
    def apply_monthly_fee(self):
        monthly_fee = 100
        if self.balance >= monthly_fee:
            print(f"Счет {self.account_number}: списание комиссии за обслуживание {monthly_fee} руб.")
            super().withdraw(monthly_fee)
        else:
            print(f"Счет {self.account_number}: недостаточно средств для списания комиссии {monthly_fee} руб.")
        self.reset_monthly_withdrawals()
    
    def __str__(self):
        return f"CheckingAccount({self.account_number}, {self.owner_name}, баланс: {self.balance:.2f} руб., комиссия за снятие: {self._withdrawal_fee} руб.)"


class Bank:
    def __init__(self, name):
        self._name = name
        self._accounts = {}
    
    @property
    def name(self):
        return self._name
    
    def add_account(self, account):
        if account.account_number in self._accounts:
            raise AccountNotFoundError(f"Счет {account.account_number} уже существует в банке")
        
        self._accounts[account.account_number] = account
        print(f"Банк '{self._name}': добавлен {account}")
    
    def get_account(self, account_number):
        if account_number not in self._accounts:
            raise AccountNotFoundError(f"Счет {account_number} не найден в банке '{self._name}'")
        return self._accounts[account_number]
    
    def transfer(self, from_account_num, to_account_num, amount):
        try:
            from_account = self.get_account(from_account_num)
            to_account = self.get_account(to_account_num)
            
            print(f"\nПеревод {amount} руб. со счета {from_account_num} на счет {to_account_num}")
            from_account.withdraw(amount)
            to_account.deposit(amount)
            print(f"Перевод успешно выполнен")
            
        except (InsufficientFundsError, NegativeAmountError, AccountNotFoundError) as e:
            print(f"Ошибка перевода: {e}")
            raise
    
    def apply_monthly_maintenance(self):
        print(f"\nМесячное обслуживание в банке '{self._name}':")
        for account in self._accounts.values():
            try:
                account.apply_monthly_fee()
            except Exception as e:
                print(f"Ошибка при обслуживании счета {account.account_number}: {e}")
    
    def get_total_balance(self):
        total = sum(account.balance for account in self._accounts.values())
        print(f"Общий баланс банка '{self._name}': {total:.2f} руб.")
        return total
    
    def list_accounts(self):
        print(f"\nСписок счетов в банке '{self._name}':")
        for account in self._accounts.values():
            print(f"   {account}")
        print()


if __name__ == "__main__":
    bank = Bank("Мой Банк")
    
    savings = SavingsAccount("SAV001", "Иван Петров", 10000, 0.05)
    checking = CheckingAccount("CHK001", "Мария Сидорова", 5000, 30)
    
    bank.add_account(savings)
    bank.add_account(checking)
    
    savings.deposit(5000)
    savings.withdraw(3000)
    savings.apply_interest()
    
    checking.deposit(2000)
    checking.withdraw(500)
    checking.withdraw(300)
    checking.withdraw(200)
    checking.withdraw(100)
    checking.withdraw(50)
    checking.withdraw(100)
    
    bank.transfer("SAV001", "CHK001", 1000)
    bank.apply_monthly_maintenance()
    bank.get_total_balance()
    bank.list_accounts()