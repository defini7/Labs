"""
Программа для демонстрации работы класса DrillingRig.
"""

from drilling_rig import DrillingRig

if __name__ == "__main__":
    rig1 = DrillingRig("Уралмаш-3000", "Тюменская обл.", 3000, 1500, 50, 1200)
    rig2 = DrillingRig("Буровая-7", "Сахалин", 4500, 2000, 60, 2000)
    
    print(rig1.drill(500))
    print(rig1.drill(1500))
    print(rig1.raise_rig())
    print(f"Нужно обслуживание? {"Да" if rig1.maintenance_needed() else "Нет"}")
    
    rig3 = DrillingRig.from_average_power("Средняя", "Краснодар", 2500, 1200, 40)
    print(rig3)
    print(f"Глубина 6000 м корректна? {"Да" if DrillingRig.validate_depth(6000) else "Нет"}")
    
    print(f"Прогресс бурения rig1: {rig1.total_depth_progress:.1f}%")
    
    print("__str__:", rig1)
    print("__repr__:", repr(rig1))
    print("__len__ ->", len(rig1))
    
    rig_sum = rig1 + rig2
    print(f"Результат сложения rig1 + rig2:\n{rig_sum}")
    print(f"rig1 >= rig2? {rig1 >= rig2}") # 1500 >= 2000 -> False
    print(f"rig2 >= rig1? {rig2 >= rig1}") # 2000 >= 1500 -> True
    