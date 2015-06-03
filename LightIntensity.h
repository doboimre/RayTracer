#ifndef LIGHTINTENSITY_H_INCLUDED
#define LIGHTINTENSITY_H_INCLUDED

class LightIntensity {
    private:
        float redIntensity;
        float greenIntensity;
        float blueIntensity;
    public:
        LightIntensity(float ri, float gi, float bi);

        float getRedIntensity() const;
        float getGreenIntensity() const;
        float getBlueIntensity() const;
};

#endif
