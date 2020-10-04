// main.cpp

#include "Student.h"
#include "GradStudent.h"

int main(int argc, char** argv) {
	Student s1(2042, "Joe Smith", 3.49, Year::FRESHMAN);
	GradStudent gs1(1455, "Linda Smith", 3.63, Year::GRADUATE, Support::TA,
									"CSE", "Performance Analysis of AI Workloads");

	cout << s1 << endl;
	s1.set_id(2402);
	s1.set_name("Pierre Darcy");
	s1.set_gpa(3.21);
	s1.set_year(Year::JUNIOR);
	cout << s1 << endl;

	cout << gs1 << endl;
	gs1.set_id(9402);
	gs1.set_name("Thomas Percy");
	gs1.set_gpa(2.21);
	gs1.set_year(Year::GRADUATE);
	gs1.set_support(Support::RA);
	gs1.set_dept("ECE");
	gs1.set_thesis("None");
	cout << gs1.get_id() << "," << gs1.get_name() << "," << gs1.get_gpa() <<
					"," << gs1.get_dept() << "," << gs1.get_thesis() << endl;

	return(0);
}
