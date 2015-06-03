#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "./Point3D.h"

class Ray {
    private:
        Point3D startPoint;
        Point3D direction;

        static float getLengthOfVector(const Point3D& startPoint, const Point3D& endPoint);
    public:
        Ray(const Point3D& startPoint, const Point3D& endPoint);

        Point3D getStartPoint() const;
        Point3D getDirection() const;

        friend float operator*(const Ray &a, const Ray &b);
};

#endif
