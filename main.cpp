#include <iostream>
#include <algorithm>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>

#include "./Display.h"
#include "./Camera.h"
#include "./Scene.h"
#include "./GraphicalObject.h"
#include "./LightSource.h"
#include "./DirectionalLightSource.h"
#include "./AmbientLightSource.h"
#include "./Sphere.h"
#include "./Plane.h"
#include "./QuadricSurface.h"
#include "./Point3D.h"
#include "./RGBColor.h"
#include "./LightIntensity.h"

unsigned int window_width = 600, window_height = 600;
const int size=window_width*window_height;

Scene setupScene();
void display();

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(window_width, window_height);
  glutCreateWindow("Hello Ray Tracing!");

  glutDisplayFunc(display);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 1.0);

  glutMainLoop();
}

Scene setupScene() {
    Scene scene;

    GraphicalObject *s1 = new Sphere(Point3D(300, 250, 400), 80, RGBColor(180, 0, 0), 1.0, 0.3, 0.4, false, false, 0.0, 0.0);
    GraphicalObject *s2 = new Sphere(Point3D(600, 550, 700), 170, RGBColor(0,0,222), 0.75, 0.3, 0.2, true, false, 0.25, 0.0);
    GraphicalObject *s3 = new Sphere(Point3D(260, 220, 300), 60, RGBColor(250,230,70), 0.75, 0.3, 0.2, false, false, 0.25, 1.4);

    GraphicalObject *plane = new Plane(Point3D(0, 135, 0), Point3D(0, 10, 0), RGBColor(0, 250, 0), 0.75, 0.75, 0.1, false, false, 0.2, 0.0);

    scene.addObject(s1);
    scene.addObject(s2);
    scene.addObject(s3);
    scene.addObject(plane);

    scene.addLightSource(new DirectionalLightSource(Point3D(600, 600, 000), LightIntensity(200.0 / 256.0, 120.0 / 256.0, 120.0 / 256.0),
                LightIntensity(1.0, 1.0, 1.0)));
    scene.addLightSource(new DirectionalLightSource(Point3D(-200, 800, 0), LightIntensity(200.0 / 256.0, 120.0 / 256.0, 120.0 / 256.0),
                LightIntensity(1.0, 1.0, 1.0)));

    scene.addLightSource(new AmbientLightSource(LightIntensity(120.0 / 256.0, 190.0 / 256.0, 160.0 / 256.0)));

    return scene;
}

void display()
{
    float *pixels = new float[size * 3];
    Scene scene = setupScene();

    Camera camera(Point3D(window_height / 2, window_width / 2, 0));
    int z = 350;

    Display display(&scene, &camera, z);
    pixels = display.getPixels(window_height, window_width, 5);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawPixels(window_width,window_height,GL_RGB,GL_FLOAT,pixels);
    glutSwapBuffers();
}
