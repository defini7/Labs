"""
Модуль для моделирования буровой установки в нефтегазовой отрасли.
Содержит класс DrillingRig, наследующий базовый класс Asset.
"""

class Asset:
    """Базовый класс актива нефтегазовой компании."""
    
    def __init__(self, name: str, location: str):
        self.name = name
        self.location = location
    
    def get_info(self):
        return f"Актив: {self.name}, расположение: {self.location}"


class DrillingRig(Asset):
    """
    Буровая установка.
    
    Attributes:
        name (str): Название установки.
        location (str): Местоположение.
        _depth_capacity (int, protected): Максимальная глубина бурения (м).
        __current_depth (int, private): Текущая глубина бурения (м).
        power (int): Мощность (кВт).
        crew_size (int): Количество персонала.
    
    Methods:
        - drill(depth): Увеличивает текущую глубину.
        - raise_rig(): Поднимает буровую вышку.
        - maintenance_needed(): Проверка необходимости ТО.
        - from_average_power(): Классовый метод.
        - validate_depth(): Статический метод.
        - total_depth_progress(): Свойство – прогресс бурения в %.
        - Спецметоды: __str__, __repr__, __len__, __add__, __ge__.
    """
    
    def __init__(self, name: str, location: str, depth_capacity: int, 
                 power: int, crew_size: int, current_depth: int = 0):
        """
        Конструктор, переопределяющий базовый класс.
        
        Args:
            name: Название установки.
            location: Местоположение.
            depth_capacity: Максимальная глубина бурения (защищённый атрибут).
            power: Мощность в кВт.
            crew_size: Размер команды.
            current_depth: Текущая глубина (приватный атрибут).
        """

        super().__init__(name, location)
        
        self._depth_capacity = depth_capacity
        self.__current_depth = current_depth
        self.power = power
        self.crew_size = crew_size

    
    def drill(self, meters: int) -> str:
        """Увеличивает текущую глубину бурения."""

        new_depth = self.__current_depth + meters

        if new_depth > self._depth_capacity:
            return f"Ошибка: превышение максимальной глубины ({self._depth_capacity} м)"
        
        self.__current_depth = new_depth

        return f"Пробурено {meters} м. Текущая глубина: {self.__current_depth} м"
    

    def raise_rig(self) -> str:
        """Поднимает буровую вышку (симуляция)."""
        return f"Буровая вышка {self.name} поднята на высоту 50 м"
    
    def maintenance_needed(self) -> bool:
        """Проверяет, нужно ли ТО (если пробурено > 80% мощности)."""
        return self.__current_depth / self._depth_capacity > 0.8

    @classmethod
    def from_average_power(cls, name: str, location: str, depth_capacity: int, 
                           avg_power: int, crew_size: int):
        """Классовый метод: создаёт установку со средней мощностью."""
        return cls(name, location, depth_capacity, avg_power, crew_size)
    
    @staticmethod
    def validate_depth(depth: int) -> bool:
        """Статический метод: проверяет корректность глубины."""
        return depth > 0 and depth < 15000

    @property
    def total_depth_progress(self) -> float:
        """Свойство: процент пробуренной глубины."""
        return (self.__current_depth / self._depth_capacity) * 100
    
    def __str__(self):
        return (f"Буровая установка '{self.name}' (глубинная ёмкость: {self._depth_capacity} м, "
                f"текущая глубина: {self.__current_depth} м, мощность: {self.power} кВт)")
    
    def __repr__(self):
        return (f"DrillingRig('{self.name}', '{self.location}', {self._depth_capacity}, "
                f"{self.power}, {self.crew_size}, {self.__current_depth})")
    
    def __len__(self) -> int:
        """Возвращает количество буровых вышек."""
        return 1
    
    def __add__(self, other):
        """
        Объединение двух буровых установок в новую с суммарными параметрами.
        """

        if not isinstance(other, DrillingRig):
            raise TypeError("Можно складывать только объекты DrillingRig")
        
        new_name = f"{self.name} & {other.name}"
        new_location = f"{self.location}/{other.location}"
        new_capacity = max(self._depth_capacity, other._depth_capacity)
        new_power = self.power + other.power
        new_crew = self.crew_size + other.crew_size
        avg_depth = (self.__current_depth + other.__current_depth) // 2
        
        return DrillingRig(new_name, new_location, new_capacity, new_power, new_crew, avg_depth)
    
    def __ge__(self, other):
        """
        Сравнение по мощности установок.
        """

        if not isinstance(other, DrillingRig):
            raise TypeError("Можно сравнивать только объекты DrillingRig")
        
        return self.power >= other.power
        