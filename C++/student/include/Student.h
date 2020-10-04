/**
 * @file Student.h
 * @brief This file implements the Student class.
 * @author Nawab Ali
 */

#ifndef STUDENT_H
#define STUDENT_H

#include<string>
#include<iostream>

using namespace std;
enum class Year{FRESHMAN, SOPHOMORE, JUNIOR, SENIOR, GRADUATE};

/**
 * @class Student
 * @brief This class creates and maintains a record for a student at a
 * university.
 */
class Student {
	protected:
		long id;
		string name;
		double gpa;
		Year y;

	public:
		/**
		 * @brief Constructor for the Student class.
		 * @param id The student identification number.
		 * @param name The name of the student (first last).
		 * @param gpa The student's GPA.
		 * @param y The year the student is enrolled in.
		 * @return None Constructor does not return anything.
		 */
		Student(long id, string name, double gpa, Year y);

		/**
		 * @brief Getter method for student identification number.
		 * @param void
		 * @return Student identification number.
		 */
		long get_id(void) const;

		/**
		 * @brief Getter method for student name.
		 * @param void
		 * @return Student name.
		 */
		string get_name(void) const;

		/**
		 * @brief Getter method for student GPA.
		 * @param void
		 * @return Student GPA.
		 */
		double get_gpa(void) const;

		/**
		 * @brief Getter method for student year.
		 * @param void
		 * @return Student year.
		 */
		Year get_year(void) const;

		/**
		 * @brief Setter method for student identification number.
		 * @param id Student identification number.
		 * @return void
		 */
		void set_id(const long id);

		/**
		 * @brief Setter method for student name.
		 * @param name Student name.
		 * @return void
		 */
		void set_name(const string name);

		/**
		 * @brief Setter method for student GPA.
		 * @param gpa Student GPA.
		 * @return void
		 */
		void set_gpa(const double gpa);

		/**
		 * @brief Setter method for student year.
		 * @param y Student year.
		 * @return void
		 */
		void set_year(const Year y);

		/**
		 * @brief Virtual function to print student record.
		 * @param out Reference to ostream object.
		 * @return Reference to ostream object.
		 */
		virtual ostream& print(ostream& out) const;

		/**
		 * @brief Overload the << operator.
		 * @param out Reference to ostream object.
		 * @param s Reference to Student object.
		 * @return Reference to ostream object.
		 */
		friend ostream& operator<<(ostream& out, const Student& s) {
			return(s.print(out));
		}
};

Student::Student(long id, string name, double gpa, Year y):
								 id(id), name(name), gpa(gpa), y(y) {
}

long Student::get_id(void) const {
	return(id);
}

string Student::get_name(void) const {
	return(name);
}

double Student::get_gpa(void) const {
	return(gpa);
}

Year Student::get_year(void) const {
	return(y);
}

void Student::set_id(const long id) {
	this->id = id;
}

void Student::set_name(const string name) {
	this->name = name;
}

void Student::set_gpa(const double gpa) {
	this->gpa = gpa;
}

void Student::set_year(const Year y) {
	this->y = y;
}

ostream& Student::print(ostream& out) const {
	out << id << "," << name << "," << gpa << ",";
	switch(y) {
		case Year::FRESHMAN:
			out << "Freshman";
			break;
		case Year::SOPHOMORE:
			out << "Sophomore";
			break;
		case Year::JUNIOR:
			out << "Junior";
			break;
		case Year::SENIOR:
			out << "Senior";
			break;
		case Year::GRADUATE:
			out << "Graduate";
			break;
		default:
			break;
	}
	return(out);
}

#endif //STUDENT_H
