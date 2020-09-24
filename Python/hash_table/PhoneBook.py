import HashTable

class PhoneBook:
    """ This class implements the Phone Book """

    def __init__(self, size):
        assert(size > 0)
        self.table = HashTable.HashTable(size)

    def add(self, name, number):
        self.table.add(name, number)

    def delete(self, name):
        self.table.delete(name)

    def find(self, name):
        return self.table.find(name)
