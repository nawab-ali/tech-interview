from __future__ import print_function
import names
import random
import PhoneBook

def gen_phone():
    """ Generate a random phone number """

    first = str(random.randint(100,999))
    second = str(random.randint(1,888)).zfill(3)

    last = (str(random.randint(1,9998)).zfill(4))
    while last in ['1111','2222','3333','4444','5555','6666','7777','8888']:
        last = (str(random.randint(1,9998)).zfill(4))

    return '{}-{}-{}'.format(first,second, last)

def main():
    local_pb = []
    iters = 1000
    pb_size = 1000

    pb = PhoneBook.PhoneBook(pb_size)

    # Add [name, number] to phonebook
    for _ in range(iters):
        name = str(names.get_full_name())
        number = str(gen_phone())

        pb.add(name, number)

        for key_val_pair in local_pb:
            if (name in key_val_pair):
                local_pb.remove(key_val_pair)

        local_pb.append([name, number])

    # Test pb.find()
    for name, number in local_pb:
        assert(number == pb.find(name))

    # Test pb.delete()
    local_pb_del = local_pb[1:iters:2]
    for name, _ in local_pb_del:
        pb.delete(name)

    for name, _ in local_pb_del:
        assert(pb.find(name) is None)

if __name__ == '__main__':
    main()
