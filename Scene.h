#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <vector>

#include "./GraphicalObject.h"
#include "./LightSource.h"
#include "./Ray.h"

class Scene {
    private:
        std::vector<GraphicalObject*> objects;
        std::vector<LightSource*> lightSources;

    public:
        void addObject(GraphicalObject *obj);
        void addLightSource(LightSource *lightSource);
                        
        GraphicalObject* getFirstIntersectingObject(const Ray &ray);
        std::vector<LightSource*> getLightSources();
};

#endif
