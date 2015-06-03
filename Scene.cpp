#include <limits>

#include "./Scene.h"

void Scene::addObject(GraphicalObject *obj) {
    this->objects.push_back(obj);
}

void Scene::addLightSource(LightSource *lightSource) {
    this->lightSources.push_back(lightSource);
}

std::vector<LightSource*> Scene::getLightSources() {
    return this->lightSources;
}

GraphicalObject* Scene::getFirstIntersectingObject(const Ray &ray) {
    GraphicalObject *obj = nullptr;
    float smallestOffset = std::numeric_limits<float>::max();

    for (GraphicalObject *o : this->objects) {
        if (o->isRayIntersecting(ray)) {
            float curOffset = o->getSmallestOffset(ray);
            if ((curOffset > 0.001) && (curOffset < smallestOffset)) {
                smallestOffset = curOffset;
                obj = o;
            }
        }
    }

    return obj;
}
