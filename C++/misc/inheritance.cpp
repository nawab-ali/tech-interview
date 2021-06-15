#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

class Shape {
public:
    virtual double area(void) = 0;
    virtual ~Shape() {}
};

class Rectangle : public Shape {
public:
    Rectangle(const double length = 0.0, const double width = 0.0) : length(length), width(width) {}

    double area(void) {
        return (length * width);
    }

    ~Rectangle() {}

protected:
    double length;
    double width;
};

class Square : public Rectangle {
public:
    Square(const double length) : Rectangle(length, length) {}
    ~Square() {}
};

class PaintJob {
public:
    PaintJob(const double cost_per_sqfeet = 0.0) : cost_per_sqfeet(cost_per_sqfeet) {}

    double cost(const double area) const {
        return (area * cost_per_sqfeet);
    }

    void set_cost_per_sqfeet(const double cost) {
        cost_per_sqfeet = cost;
    }

    virtual ~PaintJob() {}

protected:
    double cost_per_sqfeet;
};

class Circle : public Shape, public PaintJob {
public:
    Circle(const double radius = 0.0) : radius(radius) {}

    double area(void) {
        const double PI = 3.14;

        return (PI * pow(radius, 2));
    }

    ~Circle() {}

private:
    double radius;
};

double calc_area(Shape *ptr) {
    return (ptr->area());
}

int main(int argc, char **argv) {
    Circle *cptr = new Circle(9.5);
    Square *sptr = new Square(8.0);
    Rectangle *rptr = new Rectangle(7.9, 2.4);

    cout << "Circle area: " << calc_area(cptr) << endl;
    cout << "Square area: " << calc_area(sptr) << endl;
    cout << "Rectangle area: " << calc_area(rptr) << endl;

    cptr->set_cost_per_sqfeet(10.7);
    cout << "Circle paint cost: " << cptr->cost(cptr->area()) << endl;

    delete cptr;
    delete sptr;
    delete rptr;

    return 0;
}