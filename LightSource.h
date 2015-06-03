#ifndef LIGHTSOURCE_H_INCLUDED
#define LIGHTSOURCE_H_INCLUDED

enum LightSourceType {
    DIRECTIONAL_LIGHT_SOURCE = 0,
    AMBIENT_LIGHT_SOURCE
};

class LightSource {
    private:
    public:
        virtual LightSourceType getLightSourceType() const = 0;
};
#endif
