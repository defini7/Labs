import math
from typing import Tuple, List

class Shape:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y
    
    def area(self) -> float:
        raise NotImplementedError("Метод area должен быть переопределен в наследнике")
    
    def perimeter(self) -> float:
        raise NotImplementedError("Метод perimeter должен быть переопределен в наследнике")
    
    def contains_point(self, px: float, py: float) -> bool:
        raise NotImplementedError("Метод contains_point должен быть переопределен в наследнике")
    
    def intersect(self, other: "Shape") -> bool:
        if isinstance(other, Circle):
            return self._intersect_with_circle(other)
        elif isinstance(other, Rectangle):
            return self._intersect_with_rectangle(other)
        elif isinstance(other, Triangle):
            return self._intersect_with_triangle(other)
        return False
    
    def _intersect_with_circle(self, circle: "Circle") -> bool:
        raise NotImplementedError
    
    def _intersect_with_rectangle(self, rect: "Rectangle") -> bool:
        raise NotImplementedError
    
    def _intersect_with_triangle(self, triangle: "Triangle") -> bool:
        raise NotImplementedError
    
    def __str__(self) -> str:
        return f"{self.__class__.__name__}(x={self.x}, y={self.y})"


class Circle(Shape):
    def __init__(self, x: float, y: float, radius: float):
        super().__init__(x, y)
        self.radius = radius
    
    def area(self) -> float:
        return math.pi * self.radius ** 2
    
    def perimeter(self) -> float:
        return 2 * math.pi * self.radius
    
    def contains_point(self, px: float, py: float) -> bool:
        distance = math.sqrt((px - self.x) ** 2 + (py - self.y) ** 2)
        return distance <= self.radius
    
    def _intersect_with_circle(self, circle: "Circle") -> bool:
        distance = math.sqrt((self.x - circle.x) ** 2 + (self.y - circle.y) ** 2)
        return distance <= self.radius + circle.radius
    
    def _intersect_with_rectangle(self, rect: "Rectangle") -> bool:
        closest_x = max(rect.x, min(self.x, rect.x + rect.width))
        closest_y = max(rect.y, min(self.y, rect.y + rect.height))
        distance = math.sqrt((self.x - closest_x) ** 2 + (self.y - closest_y) ** 2)
        return distance <= self.radius
    
    def _intersect_with_triangle(self, triangle: "Triangle") -> bool:
        if self.contains_point(triangle.x1, triangle.y1) or \
           self.contains_point(triangle.x2, triangle.y2) or \
           self.contains_point(triangle.x3, triangle.y3):
            return True
        
        points = [(triangle.x1, triangle.y1), (triangle.x2, triangle.y2), (triangle.x3, triangle.y3)]
        for i in range(3):
            x1, y1 = points[i]
            x2, y2 = points[(i+1) % 3]
            
            ax = x2 - x1
            ay = y2 - y1
            len2 = ax*ax + ay*ay
            if len2 == 0:
                continue
            
            t = ((self.x - x1) * ax + (self.y - y1) * ay) / len2
            t = max(0, min(1, t))
            
            closest_x = x1 + t * ax
            closest_y = y1 + t * ay
            
            distance = math.sqrt((self.x - closest_x) ** 2 + (self.y - closest_y) ** 2)
            if distance <= self.radius:
                return True
        
        return False
    
    def __str__(self) -> str:
        return f"Circle(x={self.x}, y={self.y}, radius={self.radius})"


class Rectangle(Shape):
    def __init__(self, x: float, y: float, width: float, height: float):
        super().__init__(x, y)
        self.width = width
        self.height = height
    
    def area(self) -> float:
        return self.width * self.height
    
    def perimeter(self) -> float:
        return 2 * (self.width + self.height)
    
    def contains_point(self, px: float, py: float) -> bool:
        return (self.x <= px <= self.x + self.width) and (self.y <= py <= self.y + self.height)
    
    def _intersect_with_circle(self, circle: Circle) -> bool:
        return circle._intersect_with_rectangle(self)
    
    def _intersect_with_rectangle(self, rect: Rectangle) -> bool:
        return not (rect.x > self.x + self.width or
                    rect.x + rect.width < self.x or
                    rect.y > self.y + self.height or
                    rect.y + rect.height < self.y)
    
    def _intersect_with_triangle(self, triangle: Triangle) -> bool:
        if self.contains_point(triangle.x1, triangle.y1) or \
           self.contains_point(triangle.x2, triangle.y2) or \
           self.contains_point(triangle.x3, triangle.y3):
            return True
        
        if triangle.contains_point(self.x, self.y) or \
           triangle.contains_point(self.x + self.width, self.y) or \
           triangle.contains_point(self.x, self.y + self.height) or \
           triangle.contains_point(self.x + self.width, self.y + self.height):
            return True
        
        rect_edges = [
            ((self.x, self.y), (self.x + self.width, self.y)),
            ((self.x + self.width, self.y), (self.x + self.width, self.y + self.height)),
            ((self.x + self.width, self.y + self.height), (self.x, self.y + self.height)),
            ((self.x, self.y + self.height), (self.x, self.y))
        ]
        
        tri_edges = [
            ((triangle.x1, triangle.y1), (triangle.x2, triangle.y2)),
            ((triangle.x2, triangle.y2), (triangle.x3, triangle.y3)),
            ((triangle.x3, triangle.y3), (triangle.x1, triangle.y1))
        ]
        
        for (r1, r2) in rect_edges:
            for (t1, t2) in tri_edges:
                if self._segments_intersect(r1, r2, t1, t2):
                    return True
        
        return False
    
    def _segments_intersect(self, a: Tuple[float, float], b: Tuple[float, float],
                           c: Tuple[float, float], d: Tuple[float, float]) -> bool:
        def orientation(p, q, r):
            val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1])
            if val == 0: return 0
            return 1 if val > 0 else 2
        
        o1 = orientation(a, b, c)
        o2 = orientation(a, b, d)
        o3 = orientation(c, d, a)
        o4 = orientation(c, d, b)
        
        if o1 != o2 and o3 != o4:
            return True
        
        if o1 == 0 and self._on_segment(a, c, b): return True
        if o2 == 0 and self._on_segment(a, d, b): return True
        if o3 == 0 and self._on_segment(c, a, d): return True
        if o4 == 0 and self._on_segment(c, b, d): return True
        
        return False
    
    def _on_segment(self, p: Tuple[float, float], q: Tuple[float, float], r: Tuple[float, float]) -> bool:
        return (q[0] <= max(p[0], r[0]) and q[0] >= min(p[0], r[0]) and
                q[1] <= max(p[1], r[1]) and q[1] >= min(p[1], r[1]))
    
    def __str__(self) -> str:
        return f"Rectangle(x={self.x}, y={self.y}, width={self.width}, height={self.height})"


class Triangle(Shape):
    def __init__(self, x1: float, y1: float, x2: float, y2: float, x3: float, y3: float):
        center_x = (x1 + x2 + x3) / 3
        center_y = (y1 + y2 + y3) / 3
        super().__init__(center_x, center_y)
        self.x1, self.y1 = x1, y1
        self.x2, self.y2 = x2, y2
        self.x3, self.y3 = x3, y3
    
    def area(self) -> float:
        return abs((self.x1*(self.y2 - self.y3) + 
                    self.x2*(self.y3 - self.y1) + 
                    self.x3*(self.y1 - self.y2)) / 2.0)
    
    def perimeter(self) -> float:
        side1 = math.sqrt((self.x2 - self.x1)**2 + (self.y2 - self.y1)**2)
        side2 = math.sqrt((self.x3 - self.x2)**2 + (self.y3 - self.y2)**2)
        side3 = math.sqrt((self.x1 - self.x3)**2 + (self.y1 - self.y3)**2)
        return side1 + side2 + side3
    
    def contains_point(self, px: float, py: float) -> bool:
        def sign(x1, y1, x2, y2, x3, y3):
            return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)
        
        d1 = sign(px, py, self.x1, self.y1, self.x2, self.y2)
        d2 = sign(px, py, self.x2, self.y2, self.x3, self.y3)
        d3 = sign(px, py, self.x3, self.y3, self.x1, self.y1)
        
        has_neg = (d1 < 0) or (d2 < 0) or (d3 < 0)
        has_pos = (d1 > 0) or (d2 > 0) or (d3 > 0)
        
        return not (has_neg and has_pos)
    
    def _intersect_with_circle(self, circle: Circle) -> bool:
        return circle._intersect_with_triangle(self)
    
    def _intersect_with_rectangle(self, rect: Rectangle) -> bool:
        return rect._intersect_with_triangle(self)
    
    def _intersect_with_triangle(self, triangle: "Triangle") -> bool:
        def segments_intersect(p1, p2, p3, p4):
            def orientation(ax, ay, bx, by, cx, cy):
                val = (by - ay) * (cx - bx) - (bx - ax) * (cy - by)
                if val == 0: return 0
                return 1 if val > 0 else 2
            
            o1 = orientation(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1])
            o2 = orientation(p1[0], p1[1], p2[0], p2[1], p4[0], p4[1])
            o3 = orientation(p3[0], p3[1], p4[0], p4[1], p1[0], p1[1])
            o4 = orientation(p3[0], p3[1], p4[0], p4[1], p2[0], p2[1])
            
            if o1 != o2 and o3 != o4:
                return True
            
            return False
        
        t1_points = [(self.x1, self.y1), (self.x2, self.y2), (self.x3, self.y3)]
        t2_points = [(triangle.x1, triangle.y1), (triangle.x2, triangle.y2), (triangle.x3, triangle.y3)]
        
        for p in t1_points:
            if triangle.contains_point(p[0], p[1]):
                return True
        
        for p in t2_points:
            if self.contains_point(p[0], p[1]):
                return True
        
        for i in range(3):
            for j in range(3):
                if segments_intersect(t1_points[i], t1_points[(i+1)%3], 
                                     t2_points[j], t2_points[(j+1)%3]):
                    return True
        
        return False
    
    def __str__(self) -> str:
        return f"Triangle(({self.x1},{self.y1}), ({self.x2},{self.y2}), ({self.x3},{self.y3}))"
    