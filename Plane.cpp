#include <cmath>

#include "./Plane.h"

Plane::Plane(Point3D refPoint, Point3D normal, RGBColor color, float difCof, float ambCof, float specCof, 
             bool isPlaneReflective, bool isPlaneRefractive, float reflectionCoefficient, float refractionCoefficient)
    : refPoint(refPoint), normal(normal), color(color)
{
    this->diffuseCoefficient = difCof;
    this->ambientCoefficient = ambCof;
    this->specularCoefficient = specCof;
    this->isPlaneReflective = isPlaneReflective;
    this->isPlaneRefractive = isPlaneRefractive;
    this->reflectiveCoefficient = reflectionCoefficient;
    this->refractionCoefficient = refractionCoefficient;
}

bool Plane::isRayIntersecting(const Ray& ray) const {
    return (this->getOffset(ray) > 0.0);
}
       
float Plane::getSmallestOffset(const Ray &ray) const {
    return (this->getOffset(ray));
}

Point3D Plane::getClosestIntersectionPoint(const Ray &ray) const {
    return (ray.getDirection() * this->getOffset(ray) + ray.getStartPoint());
}

Ray Plane::getNormalizedNormalVectorAt(Point3D p) const {
    return Ray(p, this->normal + p); 
}
 
RGBColor Plane::getColor() const {
    return this->color;
}

float Plane::getDiffuseCoefficient() const {
    return this->diffuseCoefficient;
}

float Plane::getAmbientCoefficient() const {
    return this->ambientCoefficient;
}

float Plane::getSpecularCoefficient() const {
    return this->specularCoefficient;
}

float Plane::getOffset(const Ray &ray) const {
    float offset = -1.0;

    if (!(std::abs(this->normal * ray.getDirection()) < EPSILON)) {
        offset = ((this->refPoint - ray.getStartPoint()) * this->normal) / (this->normal * ray.getDirection());
    }

    return offset;
}

bool Plane::isReflective() const {
    return this->isPlaneReflective;
}

bool Plane::isRefractive() const {
    return this->isPlaneRefractive;
}

float Plane::getReflectionCoefficient() const {
    return this->reflectiveCoefficient;
}

float Plane::getRefractionCoefficient() const {
    return this->refractionCoefficient;
}

