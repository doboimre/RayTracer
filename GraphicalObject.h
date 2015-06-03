#ifndef GRAPHICAL_OBJECT_H_INCLUDED
#define GRAPHICAL_OBJECT_H_INCLUDED

#include "./Ray.h"
#include "./Point3D.h"
#include "./RGBColor.h"

class GraphicalObject {
    private:
    public:
        virtual bool isRayIntersecting(const Ray& ray) const = 0;
        virtual float getSmallestOffset(const Ray &ray) const = 0;
        virtual Point3D getClosestIntersectionPoint(const Ray &ray) const = 0;
        virtual Ray getNormalizedNormalVectorAt(Point3D p) const = 0;

        virtual RGBColor getColor() const = 0;
        virtual float getDiffuseCoefficient() const = 0;
        virtual float getAmbientCoefficient() const = 0;
        virtual float getSpecularCoefficient() const = 0;

        virtual bool isReflective() const = 0;
        virtual bool isRefractive() const = 0;

        virtual float getReflectionCoefficient() const = 0;
        virtual float getRefractionCoefficient() const = 0;

        virtual ~GraphicalObject() {};
};

#endif
