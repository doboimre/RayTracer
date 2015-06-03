#include <cmath>

#include "./Ray.h"
#include "./Point3D.h"

Ray::Ray(const Point3D& startPoint, const Point3D& endPoint) 
    : startPoint(startPoint),
    direction((endPoint - startPoint) / Ray::getLengthOfVector(startPoint, endPoint)) {

}
Point3D Ray::getStartPoint() const {
    return this->startPoint;
}

Point3D Ray::getDirection() const {
    return this->direction;    
}

float Ray::getLengthOfVector(const Point3D& startPoint, const Point3D& endPoint) {
    Point3D dif = endPoint - startPoint;
    return std::sqrt((std::pow(dif.getX(), 2.0) + std::pow(dif.getY(), 2.0) + std::pow(dif.getZ(), 2.0)));
}

float operator*(const Ray &a, const Ray &b) {
    Point3D aFromOrigo = a.getDirection();
    Point3D bFromOrigo = b.getDirection();

    return aFromOrigo * bFromOrigo;
}
