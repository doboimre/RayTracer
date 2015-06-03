#ifndef QUADRICSURFACE_H_INCLUDED
#define QUADRICSURFACE_H_INCLUDED

#include <vector>

#include "./RGBColor.h"
#include "./Ray.h"
#include "./Point3D.h"
#include "./GraphicalObject.h"

#define NUMBER_OF_DIMENSIONS 4

class QuadricSurface : public GraphicalObject {
    private:
        RGBColor color;
        Point3D center;

        float kd;
        float ka;
        float ks;

        std::vector< std::vector<float> > Q;

        float multiplyMatrices(const std::vector<float> a, const std::vector< std::vector<float> > q, const std::vector<float> b) const;
        float computeDiscriminant(const Ray &ray) const;
        std::vector<float> convertPointToVector(const Point3D p) const;
    public:
        QuadricSurface(Point3D center, RGBColor color, float ka, float kd, float ks, std::vector< std::vector<float> > Q);

        bool isRayIntersecting(const Ray& ray) const;
        float getSmallestOffset(const Ray &ray) const;
        Point3D getClosestIntersectionPoint(const Ray &ray) const;
        Ray getNormalizedNormalVectorAt(Point3D p) const;

        RGBColor getColor() const;
        float getDiffuseCoefficient() const;
        float getAmbientCoefficient() const;
        float getSpecularCoefficient() const;

};

#endif
