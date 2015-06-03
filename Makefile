OBJS = main.o Scene.o Camera.o Sphere.o Plane.o QuadricSurface.o Ray.o Point3D.o RGBColor.o DirectionalLightSource.o AmbientLightSource.o LightIntensity.o Display.o
CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c $(DEBUG)
LFLAGS = -std=c++11 -Wall $(DEBUG)
GL_LIBS = -lGL -lglut -lGLU

rayTracer : $(OBJS) ; $(CC) $(LFLAGS) $(OBJS) -o rayTracer $(GL_LIBS)

main.o : main.cpp ; $(CC) $(CFLAGS) main.cpp

Display.o : Display.h Display.cpp Camera.h Camera.cpp Scene.h Scene.cpp AmbientLightSource.h AmbientLightSource.cpp DirectionalLightSource.h DirectionalLightSource.cpp ; $(CC) $(CFLAGS) Display.cpp

Scene.o : Scene.h Scene.cpp GraphicalObject.h Sphere.h Sphere.cpp ; $(CC) $(CFLAGS) Scene.cpp

Camera.o : Camera.h Camera.cpp Ray.h Ray.cpp Point3D.h Point3D.cpp ; $(CC) $(CFLAGS) Camera.cpp

Sphere.o : Sphere.h Sphere.cpp GraphicalObject.h Ray.h Ray.cpp Point3D.h Point3D.cpp RGBColor.h RGBColor.cpp ; $(CC) $(CFLAGS) Sphere.cpp

Plane.o : Plane.h Plane.cpp GraphicalObject.h Ray.h Ray.cpp Point3D.h Point3D.cpp RGBColor.h RGBColor.cpp ; $(CC) $(CFLAGS) Plane.cpp

QuadricSurface.o : QuadricSurface.h QuadricSurface.cpp GraphicalObject.h Ray.h Ray.cpp Point3D.h Point3D.cpp RGBColor.h RGBColor.cpp ; $(CC) $(CFLAGS) QuadricSurface.cpp

Ray.o : Ray.h Ray.cpp Point3D.h Point3D.cpp ; $(CC) $(CFLAGS) Ray.cpp

RGBColor.o : RGBColor.h RGBColor.cpp ; $(CC) $(CFLAGS) RGBColor.cpp

Point3D.o : Point3D.h Point3D.cpp ; $(CC) $(CFLAGS) Point3D.cpp

LightIntensity.o : LightIntensity.h LightIntensity.cpp ; $(CC) $(CFLAGS) LightIntensity.cpp

DirectionalLightSource.o : LightSource.h DirectionalLightSource.h DirectionalLightSource.cpp Point3D.h Point3D.cpp LightIntensity.h LightIntensity.cpp ; $(CC) $(CFLAGS) DirectionalLightSource.cpp

AmbientLightSource.o : LightSource.h AmbientLightSource.h AmbientLightSource.cpp LightIntensity.h LightIntensity.cpp ; $(CC) $(CFLAGS) AmbientLightSource.cpp
clean : 
	\rm *.o rayTracer *~
