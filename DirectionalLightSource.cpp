#include "./LightSource.h"
#include "./DirectionalLightSource.h"
#include "./RGBColor.h"

DirectionalLightSource::DirectionalLightSource(Point3D pos, LightIntensity diffuseIntensity, LightIntensity specularIntensity) 
    : pos(pos), diffuseIntensity(diffuseIntensity), specularIntensity(specularIntensity) {
}

Point3D DirectionalLightSource::getPos() const {
    return this->pos;
}

LightSourceType DirectionalLightSource::getLightSourceType() const {
    return LightSourceType::DIRECTIONAL_LIGHT_SOURCE;
}

LightIntensity DirectionalLightSource::getDiffuseIntensity() const {
    return this->diffuseIntensity;
}

LightIntensity DirectionalLightSource::getSpecularIntensity() const {
    return this->specularIntensity;
}



