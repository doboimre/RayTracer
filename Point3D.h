#ifndef POINT_3D_H_INCLUDED
#define POINT_3D_H_INCLUDED

class Point3D {
    private:
        float x;
        float y;
        float z;
    public:
        Point3D(float x, float y, float z);

        float getX() const;
        float getY() const;
        float getZ() const;

        friend Point3D operator+(const Point3D &a, const Point3D &b);
        friend Point3D operator+(const Point3D &a, const float f);
        friend Point3D operator-(const Point3D &a, const Point3D &b);
        friend Point3D operator/(const Point3D &a, const float d);
        friend Point3D operator*(const Point3D &p, const float &t);
        friend Point3D operator*(const float &t, const Point3D &p);
        friend float operator*(const Point3D &a, const Point3D &b);
};

#endif
