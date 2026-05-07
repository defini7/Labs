class Vector2D:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __add__(self, other):
        if isinstance(other, Vector2D):
            return Vector2D(self.x + other.x, self.y + other.y)
        else:
            raise TypeError(f"Невозможно сложить Vector2D с типом {type(other).__name__}")
    
    def __str__(self):
        return f"({self.x}, {self.y})"
    