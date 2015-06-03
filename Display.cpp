#include <vector>
#include <cmath>

#include "./Display.h"

#include "./DirectionalLightSource.h"
#include "./AmbientLightSource.h"

Display::Display(Scene *scene, Camera *camera, float cameraDisplayDistance) {
    this->scene = scene;
    this->camera = camera;
    this->cameraDisplayDistance = cameraDisplayDistance;
}

float *Display::getPixels(int height, int width, int numberOfRecursions) {
    float *pixels = new float[height * width * 3];
    int colorCounter = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::vector<float> colors(this->getColorAtPixel(x, y, numberOfRecursions));
            for (int i = 0; i < 3; i++) {
                pixels[colorCounter + i] = colors[i];
            }
            colorCounter += 3;
        }
    }
    return pixels;
}

std::vector<float> Display::getColorAtPixel(int x, int y, int numberOfRecursions) {
    Ray ray = camera->getTrace(x, y, this->cameraDisplayDistance);

    return this->traceRay(ray, numberOfRecursions);
}

std::vector<float> Display::traceRay(Ray &ray, int recursionCounter) {
    std::vector<float> colors(3, 0.0);

    GraphicalObject *obj = nullptr;
    obj = scene->getFirstIntersectingObject(ray);

    if (obj == nullptr) {
        colors[0] = 0.0;
        colors[1] = 0.0;
        colors[2] = 0.0;
    }
    else {
        Point3D pointWhereTraceHit = obj->getClosestIntersectionPoint(ray);
        Ray surfaceNormal = obj->getNormalizedNormalVectorAt(pointWhereTraceHit);

        float diffuseIntensityR = 0.0;
        float diffuseIntensityG = 0.0;
        float diffuseIntensityB = 0.0;

        float ambientIntensityR = 0.0;
        float ambientIntensityG = 0.0;
        float ambientIntensityB = 0.0;

        float specularIntensityR = 0.0;
        float specularIntensityG = 0.0;
        float specularIntensityB = 0.0;
        
        for (LightSource *ls : scene->getLightSources()) {
            if (ls->getLightSourceType() == LightSourceType::DIRECTIONAL_LIGHT_SOURCE) {
                DirectionalLightSource *dirLs = (DirectionalLightSource*) ls;

                if (scene->getFirstIntersectingObject(Ray(pointWhereTraceHit, dirLs->getPos())) == nullptr) {
                    std::vector<float> diffuseIntensities = this->getDiffuseIntensities(obj, pointWhereTraceHit, surfaceNormal, dirLs);
                    std::vector<float> specularIntensities = this->getSpecularIntensities(obj, pointWhereTraceHit, surfaceNormal, dirLs);

                    diffuseIntensityR += diffuseIntensities[0];
                    diffuseIntensityG += diffuseIntensities[1];
                    diffuseIntensityB += diffuseIntensities[2];

                    specularIntensityR += specularIntensities[0];
                    specularIntensityG += specularIntensities[1]; 
                    specularIntensityB += specularIntensities[2]; 
               }
            }
            else if (ls->getLightSourceType() == LightSourceType::AMBIENT_LIGHT_SOURCE) {
                std::vector<float> ambientIntensities = this->getAmbientIntensities(obj, (AmbientLightSource*) ls);

                ambientIntensityR += ambientIntensities[0];
                ambientIntensityG += ambientIntensities[1]; 
                ambientIntensityB += ambientIntensities[2]; 
            }
        }

        std::vector<float> reflectedColors(3, 0.0);
        std::vector<float> refractedColors(3, 0.0);
        if (recursionCounter > 0) {
            if (obj->isReflective()) {
                reflectedColors = this->getReflectionIntensities(ray, pointWhereTraceHit, surfaceNormal, recursionCounter);
            }
            else if (obj->isRefractive()) {
                // TODO : put it into separate method
                float normalDotRay = surfaceNormal.getDirection() * ray.getDirection();
                float n, n1, n2;

                if (normalDotRay < 0.0) {
                    n2 = obj->getRefractionCoefficient();
                    n1 = 1.0;
//                    normalDotRay *= -1.0;
                }
                else {
                    n2 = 1.0;
                    n1 = obj->getRefractionCoefficient();
                }

                n = n1 / n2;

                Point3D refractedDir = (n * normalDotRay - std::sqrt(1.0 - n * n * (1.0 - normalDotRay * normalDotRay))) 
                                        * surfaceNormal.getDirection()
                                        - n * ray.getDirection();

                Ray refractionRay(pointWhereTraceHit + 0.001 * surfaceNormal.getDirection(), refractedDir);
                refractedColors = this->traceRay(refractionRay, recursionCounter - 1);
           }
        }

        colors[0] = obj->getColor().getNormalizedRed() * diffuseIntensityR + ambientIntensityR
                    + specularIntensityR + obj->getReflectionCoefficient() * reflectedColors[0]
                    + refractedColors[0];
        colors[1] = obj->getColor().getNormalizedGreen() * diffuseIntensityG + ambientIntensityG 
                    + specularIntensityG + obj->getReflectionCoefficient() * reflectedColors[1]
                    + refractedColors[1];
        colors[2] = obj->getColor().getNormalizedBlue() * diffuseIntensityB + ambientIntensityB 
                    + specularIntensityB + obj->getReflectionCoefficient() * reflectedColors[2]
                    + refractedColors[2];
        
    }

    return colors;
}

std::vector<float> Display::getDiffuseIntensities(GraphicalObject *obj, Point3D pointWhereTraceHit, 
                                                  Ray surfaceNormal, DirectionalLightSource *dirLs) {
    std::vector<float> diffuseColors(3, 0.0);
    
    Ray rayToLight(pointWhereTraceHit, dirLs->getPos());
    float dotProduct = std::max((float)0.0, (surfaceNormal * rayToLight)) * obj->getDiffuseCoefficient();
    diffuseColors[0] = dotProduct * dirLs->getDiffuseIntensity().getRedIntensity();
    diffuseColors[1] = dotProduct * dirLs->getDiffuseIntensity().getGreenIntensity();
    diffuseColors[2] = dotProduct * dirLs->getDiffuseIntensity().getBlueIntensity();

    return diffuseColors;
}

std::vector<float> Display::getSpecularIntensities(GraphicalObject *obj, Point3D pointWhereTraceHit,
                                                  Ray surfaceNormal, DirectionalLightSource *dirLs) {
    std::vector<float> specularIntensities(3, 0.0);

    Ray fromLightToPoint(dirLs->getPos(), pointWhereTraceHit);
    Point3D reflectedDirection( -2.0 * (surfaceNormal * fromLightToPoint) * surfaceNormal.getDirection() 
                                + fromLightToPoint.getDirection());
    Ray reflectedRay(Point3D(0.0, 0.0, 0.0), reflectedDirection);
    Ray pointToCamera(pointWhereTraceHit, camera->getPosition());

    float reflectionToCameraProduct = std::max((float) 0.0, (pointToCamera * reflectedRay)) * obj->getSpecularCoefficient();
    specularIntensities[0] += reflectionToCameraProduct * dirLs->getSpecularIntensity().getRedIntensity();
    specularIntensities[1] += reflectionToCameraProduct * dirLs->getSpecularIntensity().getGreenIntensity();
    specularIntensities[2] += reflectionToCameraProduct * dirLs->getSpecularIntensity().getBlueIntensity();

    return specularIntensities;
}

std::vector<float> Display::getAmbientIntensities(GraphicalObject *obj, AmbientLightSource *amblsrc) {
    std::vector<float> ambientIntensities(3, 0.0);

    ambientIntensities[0] += amblsrc->getAmbientIntensity().getRedIntensity() * obj->getAmbientCoefficient();
    ambientIntensities[1] += amblsrc->getAmbientIntensity().getGreenIntensity() * obj->getAmbientCoefficient();
    ambientIntensities[2] += amblsrc->getAmbientIntensity().getBlueIntensity() * obj->getAmbientCoefficient();

    return ambientIntensities;
}

std::vector<float> Display::getReflectionIntensities(Ray ray, Point3D pointWhereTraceHit, Ray surfaceNormal, int recursionCounter) {
    Ray reflectedRay(pointWhereTraceHit + 0.001 * surfaceNormal.getDirection(), 
                     (2.0 * surfaceNormal.getDirection() * (ray * surfaceNormal) - ray.getDirection()));

    return this->traceRay(reflectedRay, recursionCounter - 1);
}
 
