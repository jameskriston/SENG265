class Point:

    def __init__(self, x=0, y=0):

        self.x = x
        self.y = y

    def __repr__(self):
        
        if(self.x is None and self.y is None):
            return "Point()"
        return "Point({}, {})".format(self.x,self.y)