#include <cmath>

#include "./QuadricSurface.h"

QuadricSurface::QuadricSurface(Point3D center, RGBColor color, float ka, float kd, float ks, std::vector< std::vector<float> > Q) 
    : color(color),
      center(center) {
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->Q = Q;
}

bool QuadricSurface::isRayIntersecting(const Ray& ray) const {
    return (!(this->computeDiscriminant(ray) < 0.0));
}

float QuadricSurface::getSmallestOffset(const Ray &ray) const {
    std::vector<float> rayStartingPointVector = this->convertPointToVector(ray.getStartPoint());
    std::vector<float> rayDirectionVector = this->convertPointToVector(ray.getDirection() - this->center);

    float t1 = (-1.0 * this->multiplyMatrices(rayDirectionVector, this->Q, rayStartingPointVector)
        + std::sqrt(this->computeDiscriminant(ray)))
        / this->multiplyMatrices(rayDirectionVector, this->Q, rayDirectionVector);

    float t2 = (-1.0 * this->multiplyMatrices(rayDirectionVector, this->Q, rayStartingPointVector)
        - std::sqrt(this->computeDiscriminant(ray)))
        / this->multiplyMatrices(rayDirectionVector, this->Q, rayDirectionVector);

    return std::min(t1, t2);
}

Point3D QuadricSurface::getClosestIntersectionPoint(const Ray &ray) const {
    float smallestOffset = this->getSmallestOffset(ray);

    return ((ray.getDirection()) * smallestOffset);
}

Ray QuadricSurface::getNormalizedNormalVectorAt(Point3D p) const {
    float x = 2.0 * this->Q[0][0] * p.getX() + this->Q[0][1] * p.getY() + this->Q[0][2] * p.getZ() + this->Q[0][3];
    float y = 2.0 * this->Q[1][0] * p.getX() + this->Q[1][1] * p.getY() + this->Q[1][2] * p.getZ() + this->Q[1][3];
    float z = 2.0 * this->Q[2][0] * p.getX() + this->Q[2][1] * p.getY() + this->Q[2][2] * p.getZ() + this->Q[2][3];

    return Ray(Point3D(x,y,z), Point3D(x,y,z * 1.1));
}

RGBColor QuadricSurface::getColor() const {
    return this->color;
}

float QuadricSurface::getDiffuseCoefficient() const {
    return this->kd;
}

float QuadricSurface::getAmbientCoefficient() const {
    return this->ka;
}

float QuadricSurface::getSpecularCoefficient() const {
    return this->ks;
}

float QuadricSurface::computeDiscriminant(const Ray &ray) const {
    std::vector<float> rayDirectionVector = this->convertPointToVector(ray.getDirection() -  this->center);
    std::vector<float> rayStartingPointVector = this->convertPointToVector(ray.getStartPoint());

    float determinant = std::pow(this->multiplyMatrices(rayDirectionVector, this->Q, rayStartingPointVector), 2.0)
                        - (this->multiplyMatrices(rayDirectionVector, this->Q, rayDirectionVector) 
                         * this->multiplyMatrices(rayStartingPointVector, this->Q, rayStartingPointVector));
    
    return determinant;
}

float QuadricSurface::multiplyMatrices(const std::vector<float> a, const std::vector< std::vector<float> > q, const std::vector<float> b) const {
    std::vector<float> tmp;

    for (int i = 0; i < NUMBER_OF_DIMENSIONS; i++) {
        float tmp_entry = 0.0;
        for (int j = 0; j < NUMBER_OF_DIMENSIONS; j++) {
            tmp_entry += a[j] * q[j][i];
        }
        tmp.push_back(tmp_entry);
    }

    float res = 0.0;
    for (int i = 0; i < NUMBER_OF_DIMENSIONS; i++) {
        res += tmp[i] * b[i];
    }

    return res;
}

std::vector<float> QuadricSurface::convertPointToVector(const Point3D p) const {
    std::vector<float> vec;
    vec.push_back(p.getX());
    vec.push_back(p.getY());
    vec.push_back(p.getZ());
    vec.push_back(1.0);

    return vec;
}
