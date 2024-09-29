#!/usr/bin/python3

class Student:
    def __init__(self, name):
        self.name = name

    def print_info(self):
        print(self.name)

class GradStudent(Student):
    def __init__(self, name, thesis):
        super().__init__(name)
        self.thesis = thesis

    def print_info(self):
        super().print_info()
        print(self.thesis)

def main():
    student = Student('Mary Smith')
    grad = GradStudent('Johnny Appleseed', 'How to grow apples')

    student.print_info()
    grad.print_info()

if __name__ == '__main__':
    main()
