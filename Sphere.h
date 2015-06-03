#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include "./GraphicalObject.h"
#include "./Point3D.h"
#include "./RGBColor.h"
#include "./Ray.h"

class Sphere : public GraphicalObject {
    private:
        Point3D center;
        float r;

        RGBColor color;
        float diffuseCoefficient;
        float ambientCoefficient;
        float specularCoefficient;

        bool isSphereReflective;
        bool isSphereRefractive;

        float reflectionCoefficient;
        float refractionCoefficient;
    public:
        Sphere(Point3D c, float r, RGBColor color, float kd, float ka, float ks, 
               bool isSphereReflective, bool isSphereRefractive, float reflectionCoefficient,
               float refractionCoefficient);

        bool isRayIntersecting(const Ray &ray) const;
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
