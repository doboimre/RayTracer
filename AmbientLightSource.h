#ifndef AMBIENTLIGHTSOURCE_H_INCLUDED
#define AMBIENTLIGHTSOURCE_H_INCLUDED

#include "./LightSource.h"
#include "./LightIntensity.h"

class AmbientLightSource : public LightSource {
    private:
        LightIntensity ambientIntensity;
    public:
        AmbientLightSource(LightIntensity ambientIntensity);

        LightSourceType getLightSourceType() const;
        LightIntensity getAmbientIntensity() const;
};

#endif
