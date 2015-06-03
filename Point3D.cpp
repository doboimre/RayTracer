#include "./Point3D.h"

Point3D::Point3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float Point3D::getX() const {
    return this->x;
}

float Point3D::getY() const {
    return this->y;
}

float Point3D::getZ() const {
    return this->z;
}

Point3D operator+(const Point3D &a, const Point3D &b) {
    return Point3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point3D operator+(const Point3D &a, const float f) {
    return Point3D(a.x + f, a.y + f, a.z + f);
}

Point3D operator-(const Point3D &a, const Point3D &b) {
    return Point3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

Point3D operator/(const Point3D &a, const float d) {
    return Point3D(a.getX() / d, a.getY() / d, a.getZ() / d);
}

Point3D operator*(const Point3D &p, const float &t) {
    return Point3D(p.x * t, p.y * t, p.z * t);
}
Point3D operator*(const float &t, const Point3D &p) {
    return Point3D(p.x * t, p.y * t, p.z * t);
}

float operator*(const Point3D &a, const Point3D &b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}
