#include "./LightIntensity.h"

LightIntensity::LightIntensity(float ri, float gi, float bi) {
    this->redIntensity = ri;
    this->greenIntensity = gi;
    this->blueIntensity = bi;
}

float LightIntensity::getRedIntensity() const {
    return this->redIntensity;
}

float LightIntensity::getGreenIntensity() const {

    return this->greenIntensity;
}

float LightIntensity::getBlueIntensity() const {

    return this->blueIntensity;
}

