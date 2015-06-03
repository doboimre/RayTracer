#include "./RGBColor.h" 

RGBColor::RGBColor(int red, int green, int blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

float RGBColor::getNormalizedRed() const {
    return ((float)this->red / COLOR_SCALE);
}

float RGBColor::getNormalizedGreen() const {
    return ((float)this->green / COLOR_SCALE);
}

float RGBColor::getNormalizedBlue() const {
    return ((float)this->blue / COLOR_SCALE);
}

