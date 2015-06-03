#include "./AmbientLightSource.h"

AmbientLightSource::AmbientLightSource(LightIntensity ambientIntensity) : ambientIntensity(ambientIntensity) {

}

LightSourceType AmbientLightSource::getLightSourceType() const {
    return LightSourceType::AMBIENT_LIGHT_SOURCE;
}

LightIntensity AmbientLightSource::getAmbientIntensity() const {
    return this->ambientIntensity;
}
