class HashTable:
    """ This class implements a hash table """

    def __init__(self, size):
        assert(size > 0)

        # In case of collisions, chain the values
        self.size = size
        self.container = [[None] for i in range(size)]

    def _hash(self, key, x = 263, p = 1000000007):
        """ Return hash of key """

        hash_val = 0

        for i in range(len(key)):
            hash_val += (ord(key[i]) * pow(x, i))
            hash_val %= p

        return hash_val % self.size

    def add(self, key, value):
        """ Add [key, value] pair to hash table """

        # Calculate index using hash function
        index = self._hash(key)
        assert(index >= 0 and index < len(self.container))

        # In case of collisions, chain the values
        h_list = self.container[index]

        # Remove duplicate entries for key
        for key_val_pair in h_list:
            if key_val_pair is not None and key in key_val_pair:
                h_list.remove(key_val_pair)

        # Insert new entry for [key, value]
        h_list.insert(0, [key, value])

    def delete(self, key):
        """ Delete [key, value] pair from hash table """

        # Calculate index using hash function
        index = self._hash(key)
        assert(index >= 0 and index < len(self.container))

        # If key matches, delete [key, value]
        h_list = self.container[index]

        for key_val_pair in h_list:
            if key_val_pair is not None and key in key_val_pair:
                h_list.remove(key_val_pair)

    def find(self, key):
        """ Return [key, value] pair """

        # Calculate index using hash function
        index = self._hash(key)
        assert(index >= 0 and index < len(self.container))

        h_list = self.container[index]

        for key_val_pair in h_list:
            if key_val_pair is not None and key in key_val_pair:
                return key_val_pair[1]

        return None
