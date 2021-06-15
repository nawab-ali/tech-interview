#include <iostream>

using namespace std;

template<class T>
class Point {
public:
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    Point(const Point<T> &p);
    Point<T> operator+(const Point<T> &p);
    Point<T> &operator=(const Point<T> &p);
    bool operator==(const Point<T> &p);

    friend ostream &operator<<(ostream &out, const Point<T> &p) {
        out << "[" << p.x << ", " << p.y << "]";
        return (out);
    }

    pair <T, T> get_coordinates(void);
    void set_coordinates(const T x, const T y);

private:
    T x;
    T y;
};

template<class T>
Point<T>::Point(const Point<T> &p) : Point(p.x, p.y) {}

template<class T>
Point<T> Point<T>::operator+(const Point<T> &p) {
    return (Point(x + p.x, y + p.y));
}

template<class T>
Point<T> &Point<T>::operator=(const Point<T> &p) {
    x = p.x;
    y = p.y;

    return (*this);
}

template<class T>
bool Point<T>::operator==(const Point<T> &p) {
    return (x == p.x && y == p.y);
}

template<class T>
pair <T, T> Point<T>::get_coordinates(void) {
    return (make_pair(x, y));
}

template<class T>
void Point<T>::set_coordinates(const T x, const T y) {
    this->x = x;
    this->y = y;
}

int main(int argc, char **argv) {
    Point<int> p1;
    Point<double> p4;
    Point<double> p2 = Point<double>(2.0, 3.5);
    Point<double> p3 = p2;
    pair<int, int> coordinates;

    p4 = p2;

    cout << p1 << endl;
    cout << p2 << endl;
    cout << p4 << endl;
    cout << p3 << endl;
    cout << p2 + p3 << endl;
    cout << (p1 == Point<int>(2, 3)) << endl;
    cout << (p2 == p4) << endl;
    p1.set_coordinates(7, 12);
    cout << p1 << endl;
    coordinates = p1.get_coordinates();
    cout << coordinates.first << ", " << coordinates.second << endl;

    return 0;
}