#include "./Camera.h"
#include "./Ray.h"
#include "./Point3D.h"

Camera::Camera(Point3D initialPos) : pos(initialPos) {

}

Point3D Camera::getPosition() const {
    return this->pos;
}

Ray Camera::getTrace(float x, float y, float z) {
    return Ray(this->pos, Point3D(x,y,z));
}
