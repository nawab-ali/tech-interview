/**
 * @file GradStudent.h
 * @brief This file implements the GradStudent class.
 * @author Nawab Ali
 */

#ifndef GRADSTUDENT_H
#define GRADSTUDENT_H

#include "Student.h"

enum class Support{TA, RA, FELLOW, OTHER};

/**
 * @class GradStudent
 * @brief This class creates and maintains records for a graduate student at
 * a university.
 */
class GradStudent : public Student {
	protected:
		Support s;
		string dept;
		string thesis;

	public:
		/**
		 * @brief Constructor for the GradStudent class.
		 * @param id The student identification number.
		 * @param name The name of the student (first last).
		 * @param gpa The student's GPA.
		 * @param y The year the student is enrolled in.
		 * @param s The financial support that the student receives.
		 * @param dept The student's academic dept.
		 * @param thesis The student's thesis title.
		 * @return None Constructor does not return anything.
		 */
		GradStudent(long id, string name, double gpa, Year y, Support s,
								string dept, string thesis);

		/**
		 * @brief Getter method for student's financial support.
		 * @param void
		 * @return Student's financial support.
		 */
		Support get_support(void) const;

		/**
		 * @brief Getter method for student's academic dept.
		 * @param void
		 * @return Student's academic dept.
		 */
		string get_dept(void) const;

		/**
		 * @brief Getter method for student's thesis title.
		 * @param void
		 * @return Student's thesis title.
		 */
		string get_thesis(void) const;

		/**
		 * @brief Setter method for student's financial support.
		 * @param s Student's financial support.
		 * @return void
		 */
		void set_support(const Support s);

		/**
		 * @brief Setter method for student's academic dept.
		 * @param dept Student's academic dept.
		 * @return void
		 */
		void set_dept(const string dept);

		/**
		 * @brief Setter method for student's thesis title.
		 * @param thesis Student's thesis title.
		 * @return void
		 */
		void set_thesis(const string thesis);

		/**
		 * @brief Virtual function to print graduate student record.
		 * @param out Reference to ostream object.
		 * @return Reference to ostream object.
		 */
		ostream& print(ostream& out) const;
};

GradStudent::GradStudent(long id, string name, double gpa, Year y, Support s,
												 string dept, string thesis):
												 Student(id, name, gpa, y),
												 s(s), dept(dept), thesis(thesis) {
}

Support GradStudent::get_support(void) const {
	return(s);
}

string GradStudent::get_dept(void) const {
	return(dept);
}

string GradStudent::get_thesis(void) const {
	return(thesis);
}

void GradStudent::set_support(const Support s) {
	this->s = s;
}

void GradStudent::set_dept(const string dept) {
	this->dept = dept;
}

void GradStudent::set_thesis(const string thesis) {
	this->thesis = thesis;
}

ostream& GradStudent::print(ostream& out) const {
	Student::print(out);
	out << ",";

	switch(s) {
		case Support::TA:
			out << "TA";
			break;
		case Support::RA:
			out << "RA";
			break;
		case Support::FELLOW:
			out << "Fellow";
			break;
		case Support::OTHER:
			out << "Other";
			break;
		default:
			break;
	}

	out << "," << dept << "," << thesis;
	return(out);
}

#endif //GRADSTUDENT_H
