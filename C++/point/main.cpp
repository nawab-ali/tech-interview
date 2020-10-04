#include "point.h"

int main(int argc, char** argv) {
	Point p1;
	Point p2(3.61);
	Point p3(2.53, 3.02);
	Point p4 = p2 + p3;

	cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	cout << p4 << endl;

	return(0);
}
