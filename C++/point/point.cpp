// This class represents the cartesian point.

#include "point.h"

Point::Point(const Point& p) {
	x = p.getx();
	y = p.gety();
}

double Point::getx(void) const {
	return(x);
}

double Point::gety(void) const {
	return(y);
}

void Point::setx(const double x) {
	this->x = x;
}

void Point::sety(const double y) {
	this->y = y;
}

Point Point::operator+ (const Point& p) {
	Point p1;
	p1.setx(this->x + p.getx());
	p1.sety(this->y + p.gety());
	return(p1);
}

Point::~Point() {}

ostream& operator<< (ostream& out, const Point& p) {
	out << "(" << p.getx() << ", " << p.gety() << ")";
	return(out);
}
