#pragma once
#include "Image.h"

class Coord {
public:
    double _x, _y, _z;
    Coord(double x, double y, double z);
    ~Coord() {};
};

class Face {
public:
    unsigned int _v[4];
    Face(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4);
    ~Face() {};
};

class ThreeD {
public:
    int _sizeCoord;
    int _sizeFace;
    Coord* _coord;
    Face* _face;

    ThreeD(const char* filename);
    ~ThreeD();

    void provSet(Image& image, Color3 color, double cof, double offsetX, double offsetY, double fi=0.0, double psi=0., double nu=0.);
    void polSet(Image& image, Color3 color, double cof, double offsetX, double offsetY, double fi=0, double psi=0, double nu=0);
    void triangle(Face face, Image& image, Color3 color, double cof, double offsetX, double offsetY, double* z_buf);

};