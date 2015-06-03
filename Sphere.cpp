#include <algorithm>
#include <cmath>

#include "./GraphicalObject.h"
#include "./Sphere.h"

Sphere::Sphere(Point3D c, float r, RGBColor color, float kd, float ka, float ks, 
               bool isSphereReflective, bool isSphereRefractive, float reflectionCoefficient,
               float refractionCoefficient)
    : center(c), color(color) {
    this->r = r;
    this->diffuseCoefficient = kd;
    this->ambientCoefficient = ka;
    this->specularCoefficient = ks;
    this->isSphereReflective = isSphereReflective;
    this->isSphereRefractive = isSphereRefractive;
    this->reflectionCoefficient = reflectionCoefficient;
    this->refractionCoefficient = refractionCoefficient;
}

bool Sphere::isRayIntersecting(const Ray& ray) const {
    float a = ray.getDirection() * ray.getDirection();
    float b = 2.0 * ray.getDirection() * (ray.getStartPoint() - this->center);
    float c = ((ray.getStartPoint() - this->center) * (ray.getStartPoint() - this->center)) - (this->r * this->r);

    return (std::sqrt(b * b - 4.0 * a * c) > 0.0);
}

Point3D Sphere::getClosestIntersectionPoint(const Ray &ray) const {
    float offset = this->getSmallestOffset(ray);

    return (ray.getDirection() * offset + ray.getStartPoint());
}

Ray Sphere::getNormalizedNormalVectorAt(Point3D p) const {
    return Ray(this->center, p);
}

float Sphere::getSmallestOffset(const Ray &ray) const {
    float a = ray.getDirection() * ray.getDirection();
    float b = 2.0 * ray.getDirection() * (ray.getStartPoint() - this->center);
    float c = ((ray.getStartPoint() - this->center) * (ray.getStartPoint() - this->center)) - (this->r * this->r);

    float l1 = (-b + std::sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
    float l2 = (-b - std::sqrt(b * b - 4.0 * a * c)) / (2.0 * a);

    float res;
    if ((l1 > -0.0001) && (l2 > -0.0001)) {
        res = std::min(l1, l2);
    }
    else if (l1 > -0.0001) {
        res = l1;
    }
    else {
        res = l2;
    }

    return res;
}

RGBColor Sphere::getColor() const {
    return this->color;
}

float Sphere::getDiffuseCoefficient() const {
    return this->diffuseCoefficient;
}

float Sphere::getAmbientCoefficient() const {
    return this->ambientCoefficient;
}

float Sphere::getSpecularCoefficient() const {
    return this->specularCoefficient;
}

bool Sphere::isReflective() const {
    return this->isSphereReflective;    
}

bool Sphere::isRefractive() const {
    return this->isSphereRefractive;
}

float Sphere::getReflectionCoefficient() const {
    return this->reflectionCoefficient;
}

float Sphere::getRefractionCoefficient() const {
    return this->refractionCoefficient;
}
