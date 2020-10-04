// This class represents the cartesian point.

#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

class Point {
	private:
		double x;
		double y;

	public:
		Point(const double x = 0.0, const double y = 0.0) : x(x), y(y) {}
		Point(const Point& p);
		double getx(void) const;
		double gety(void) const;
		void setx(const double x);
		void sety(const double y);
		Point operator+ (const Point& p);
		~Point();
};

ostream& operator<< (ostream& out, const Point& p);

#endif //POINT_H
