# Fill your boots here...
# Replace this file with your solution from part B.class Point:
import math

class Point:

    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __repr__(self):
        return "Point(%r, %r)" % (self.x, self.y)

    def delta_x(self, dx):
        
        return Point(self.x+dx, self.y)

    def delta_y(self,dy):
        
        return Point(self.x,self.y+dy)
    
    def translate(self,dx,dy):
        return Point(self.x+dx,self.y+dy)


class Circle:
        
    def __init__(self, center, radius=0):
        self.center = center
        self.radius = radius

    def __repr__(self):
        return "Circle(%r, %r)" % (self.center, self.radius)

    def area(self):
        
        area = math.pi * ((math.pow((self.radius),2)))
        return area
    
    def perimeter(self):

        perimeter = 2 * math.pi * self.radius
        return perimeter
    
    def translate(self,dx,dy):
        new_center = self.center.translate(dx,dy)
        return Circle(new_center,self.radius)
    
class Rectangle:

        def __init__(self, upleft,lowright):
            self.upleft = upleft
            self.lowright = lowright

        def __repr__(self):
            return "Rectangle(%r, %r)" % (self.upleft,self.lowright)
        
        def area(self):
            length = abs(self.lowright.x - self.upleft.x)
            width = abs(self.upleft.y - self.lowright.y)
            return (length*width)
        
        def perimeter(self):
            return (2 * (abs(self.lowright.x - self.upleft.x)+abs(self.upleft.y - self.lowright.y)))
        
        def translate(self,dx,dy):
            
            new_upleft = self.upleft.translate(dx,dy)
            new_lowright = self.lowright.translate(dx,dy)

            return Rectangle(new_upleft,new_lowright)
        






