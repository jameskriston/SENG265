from customer import Customer

class Controller:

    def __init__(self):
        self.customers = {}
        self.current_customer = None

    def search_customer(self, key):
        return self.customers.get(key)

    def create_customer(self, number, name, birth_year):
        if not self.search_customer(number):
            customer = Customer(number, name, birth_year)
            self.customers[number] = customer
            return True
        else:
            return False

    def set_current_customer(self, key):
        current = self.search_customer(key)
        self.current_customer = current
        

    def get_current_customer(self):
        return self.current_customer


    def unset_current_customer(self):
        self.current_customer = None