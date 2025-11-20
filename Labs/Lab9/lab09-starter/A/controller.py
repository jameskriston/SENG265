from product import Product
import hashlib

class Controller:
    def __init__(self):
        self.products = []
        self.users = {}
        self.load_users()

    def load_users(self):
        users = {}
        try:
            with open("users.txt", "r") as f:
                for line in f:
                    line = line.strip()
                    if not line:
                        continue
                    split_line = line.split(",")
                    if len(split_line) != 2:
                        continue
                    user = split_line[0].strip()
                    hashpass = split_line[1].strip()
                    users[user] = hashpass
            
            self.users = users
        except FileNotFoundError:
          self.users = False


        # TODO: complete the load_users method. To do so:
        # Read the data from the file users.txt and fill out the users dictionary 
        # with each username as the key and each password hash as the value


    def get_password_hash(self, password):
        # Learn a bit about password hashes by reading this code
        encoded_password = password.encode('utf-8')     # Convert the password to bytes
        hash_object = hashlib.sha256(encoded_password)      # Choose a hashing algorithm (e.g., SHA-256)
        hex_dig = hash_object.hexdigest()       # Get the hexadecimal digest of the hashed password
        return hex_dig

    def login(self, username, password):
        # notice that we convert the password into a password hash before
        # comparing it with the password hash that came from the file
        if self.users.get(username):
            password_hash = self.get_password_hash(password)
            if self.users.get(username) == password_hash:
                return True
            else:
                return False
        else:
            return False

    def search_product(self, key):
        for product in self.products:
            if (product.code == key):
                return product
        return None

    def create_product(self, code, description, price):
        if not self.search_product(code):
            product = Product(code, description, price)
            self.products.append(product)
            return True
        else:
            return False


