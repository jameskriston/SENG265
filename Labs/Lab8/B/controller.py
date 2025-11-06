from product import Product

class Controller:
    def __init__(self):
        self.product_list = []
        

    def search_product(self, key):
        if len(self.product_list) is None:
            return None
        for product in self.product_list:
            if(product.code == key):
                return product
            
        return None    


    def create_product(self, code, description, price):
        if(self.search_product(code) is None):
            new_product = Product(code,description,price)
            self.product_list.append(new_product)
            return new_product
        return False