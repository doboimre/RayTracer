#ifndef RGB_COLOR_H_INCLUDED
#define RGB_COLOR_H_INCLUDED

#define COLOR_SCALE 256.0

class RGBColor {
    private:
        int red;
        int green;
        int blue;
    public:
        RGBColor(int red, int green, int blue);

        float getNormalizedRed() const;
        float getNormalizedGreen() const;
        float getNormalizedBlue() const;
};

#endif
