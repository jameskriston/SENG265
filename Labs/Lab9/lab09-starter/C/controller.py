from product_encoder import ProductEncoder
from product_decoder import ProductDecoder
import json
from product import Product

class Controller:
    def __init__(self):
        # TODO: how should you change the constructor to load the data from the file?
        self.products = []

        # HINTS: In the constructor, you will initialize the self.products list
        # Either you load the data from the json file if the file exists
        # Or you start with an empty self.products list
        self.filename = 'products.json'
        try:
            with open(self.filename, "r") as file:
                self.products = json.load(file, cls=ProductDecoder)

            # TODO: What should you do here?
            
        except:
            # TODO: and here?
            self.products = []

    def search_product(self, key):
        for product in self.products:
            if (product.code == key):
                return product
        return None

    def create_product(self, code, description, price):
        if not self.search_product(code):
            product = Product(code, description, price)
            self.products.append(product)
            # here you will save the file after creating a product
            # TODO: What should you do here?
            with  open(self.filename, "w") as file:
                json.dump(self.products, file, cls=ProductEncoder, indent=1)
            return True
        else:
            return False


