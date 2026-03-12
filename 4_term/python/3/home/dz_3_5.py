from math import pi


ERROR = "invalid file format, expected pairs (x;y) separated by spaces or new lines"


def sgn(n):
    if n == 0:
        return 0
    
    return 1 if n > 0 else -1


def is_convex(verts):
    sign = None
    count = len(verts)

    for i in range(count):
        x0, y0 = verts[i]
        x1, y1 = verts[(i + 1) % count]
        x2, y2 = verts[(i + 2) % count]

        cross = (x1 - x0) * (y2 - y1) - (y1 - y0) * (x2 - x1)

        if sign is None:
            sign = sgn(cross)
        else:
            if sgn(cross) != sign:
                return False
            
    return True


def is_point_inside(verts, x, y):
    inside = False
    
    n = len(verts)

    for i in range(n):
        x1, y1 = verts[i]
        x2, y2 = verts[(i + 1) % n]
        
        if not(y1 > y and y2 > y):
            x_intersect = x1 + (y - y1) * (x2 - x1) / (y2 - y1)
            
            if x_intersect > x:
                inside = not inside
                
    return inside


with open("5.txt") as f:
    content = f.read()

verts = []

for coord in content.split():
    coords = coord.split(";")

    if len(coords) != 2 or coords[0][0] != "(" or coords[1][-1] != ")":
        raise SyntaxError(ERROR)

    verts.append((int(coords[0][1:]), int(coords[1][:-1])))

if is_convex(verts):
    print("Полигон выпуклый")
else:
    print("Полигон невыпуклый")

x, y = map(float, input("Точка: ").split())

if is_point_inside(verts, x, y):
    print("Точка внутри")
else:
    print("Точка снаружи")
