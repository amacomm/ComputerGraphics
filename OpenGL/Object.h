#pragma once
#include "Image.h"

class Coord {
public:
    double _x, _y, _z;
    Coord(double x, double y, double z);
    ~Coord() {};
};

class Norm {
public:
    double _x, _y, _z;
    Norm(double x, double y, double z);
    ~Norm() {};
};

class Face {
public:
    unsigned int* _v;
    int size;
    Face();
    ~Face() {
        if(!_v)
        delete[] _v;
    }
    void add(unsigned int v);
};

class ThreeD {
public:
    int _sizeCoord;
    int _sizeFace;
    int _sizeNorm;
    Coord* _coord;
    Face* _face;
    Norm* _norm;

    ThreeD(const char* filename);
    ~ThreeD();

    void provSet(Image& image, Color3 color, double cof, double offsetX, double offsetY, double fi=0.0, double psi=0., double nu=0.);
    void polSet(Image& image, Color3 color, double cof, double offsetX, double offsetY, double fi=0, double psi=0, double nu=0);
    void triangle(Face face, Image& image, Color3 color, double cof, double offsetX, double offsetY, double* z_buf);

};