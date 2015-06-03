#ifndef DIRECTIONALLIGHTSOURCE_H_INCLUDED
#define DIRECTIONALLIGHTSOURCE_H_INCLUDED

#include "./LightSource.h"
#include "./Point3D.h"
#include "./LightIntensity.h"

class DirectionalLightSource : public LightSource {
    private:
        Point3D pos;
        LightIntensity diffuseIntensity;
        LightIntensity specularIntensity;
    public:
        DirectionalLightSource(Point3D pos, LightIntensity diffuseIntensity, LightIntensity specularIntensity);

        LightSourceType getLightSourceType() const;
        LightIntensity getDiffuseIntensity() const;
        LightIntensity getSpecularIntensity() const;

        Point3D getPos() const;
};

#endif
