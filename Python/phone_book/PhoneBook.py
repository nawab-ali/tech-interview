class PhoneBook:
    """ This class implements the Phone Book """

    def __init__(self):
        self.name = {}
        self.number = {}

    def add(self, name, number):
        self.name[name] = number
        self.number[number] = name

    def delete_name(self, name):
        number = self.name.pop(name, None)
        if number:
            self.number.pop(number, None)

    def delete_number(self, number):
        name = self.number.pop(number, None)
        if name:
            self.name.pop(name, None)

    def find_number(self, name):
        if name in self.name:
            return self.name[name]

    def find_name(self, number):
        if number in self.number:
            return self.number[number]
