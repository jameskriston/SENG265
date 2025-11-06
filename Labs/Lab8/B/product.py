class Product:
  def __init__(self,code, description, price):
    # code will be the key
    self.code = code
    self.description = description
    self.price = price

  def __str__(self):
    return f"code: {self.code}, description: {self.description}, price: {self.price:.2f}"


  def __eq__(self, other):
    return self.code  == other.code and self.description == other.description \
    and self.price == other.price

