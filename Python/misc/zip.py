#!/home/ubuntu/wspace-2/anaconda2/bin/python

def main():
    student_names = ['John', 'Sarah', 'Ted']
    student_ids = [1006, 1007, 1008]
    student_grades = ['B', 'A', 'C']

    student_records = zip(student_names, student_ids, student_grades)

    print student_records

    unzipped_names, unzipped_ids, unzipped_grades = zip(*student_records)
    print unzipped_names, unzipped_ids, list(unzipped_grades)

if __name__ == '__main__':
    main()
