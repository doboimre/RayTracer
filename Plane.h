#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

#include "./GraphicalObject.h"
#include "./RGBColor.h"
#include "./Point3D.h"

#define EPSILON 0.0001

class Plane : public GraphicalObject {
    private:
        Point3D refPoint;
        Point3D normal;

        RGBColor color;
        float diffuseCoefficient;
        float ambientCoefficient;
        float specularCoefficient;

        bool isPlaneReflective;
        bool isPlaneRefractive;

        float reflectiveCoefficient;
        float refractionCoefficient;

        float getOffset(const Ray &ray) const;
    public:
        Plane(Point3D refPoint, Point3D normal, RGBColor color, float difCof, float ambCof, float specCof, 
              bool isPlaneReflective, bool isPlaneRefractive, float reflectionCoefficient, float refractionCoefficient);
        bool isRayIntersecting(const Ray& ray) const;
        float getSmallestOffset(const Ray &ray) const;
        Point3D getClosestIntersectionPoint(const Ray &ray) const;
        Ray getNormalizedNormalVectorAt(Point3D p) const;
        
        RGBColor getColor() const;
        float getDiffuseCoefficient() const;
        float getAmbientCoefficient() const;
        float getSpecularCoefficient() const;

        bool isReflective() const;
        bool isRefractive() const;

        float getReflectionCoefficient() const;
        float getRefractionCoefficient() const;
};

#endif







