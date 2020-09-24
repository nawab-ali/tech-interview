import PhoneBook

def main():
    pb = PhoneBook.PhoneBook()

    pb.add('John Smith', 7243565567)
    print(pb.find_number('John Smith'))
    print(pb.find_name(7243565567))

    print(pb.find_number('Smith'))
    print(pb.find_name(703709484))

    pb.delete_name('Jane Doe')
    pb.delete_number(7602417245)

    pb.delete_number(7243565567)
    print(pb.find_name(7243565567))

if __name__ == '__main__':
    main()
