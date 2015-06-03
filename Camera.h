#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "./Point3D.h"
#include "./Ray.h"

class Camera {
    private:
        Point3D pos;
    public:
        Camera(Point3D initialPos);

        Point3D getPosition() const;

        Ray getTrace(float x, float y, float z);
};

#endif
