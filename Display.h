#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <vector>
#include "./Scene.h"
#include "./Camera.h"
#include "./Point3D.h"
#include "./GraphicalObject.h"
#include "./Ray.h"
#include "./DirectionalLightSource.h"
#include "./AmbientLightSource.h"

class Display {
    private:
        Scene *scene;
        Camera *camera;
        float cameraDisplayDistance;

        std::vector<float> getColorAtPixel(int x, int y, int numberOfRecursions);
        std::vector<float> traceRay(Ray &ray, int recursionCounter);
        std::vector<float> getDiffuseIntensities(GraphicalObject *obj, Point3D pointWhereTraceHit, 
                                                 Ray surfaceNormal, DirectionalLightSource *dirLs);
        std::vector<float> getSpecularIntensities(GraphicalObject *obj, Point3D pointWhereTraceHit,
                                                  Ray surfaceNormal, DirectionalLightSource *dirLs);
        std::vector<float> getAmbientIntensities(GraphicalObject *obj, AmbientLightSource *amblsrc);
        std::vector<float> getReflectionIntensities(Ray ray, Point3D pointWhereTraceHit,
                                                   Ray surfaceNormal, int recursionCounter);
    public:                                       
        Display(Scene *scene, Camera *camera, float cameraDisplayDistance);

        float *getPixels(int height, int width, int numberOfRecursions);

};

#endif
