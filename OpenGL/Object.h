#pragma once
#include "Image.h"

class Coord {
public:
    float _x, _y, _z;
    Coord(float x, float y, float z);
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
    //unsigned int* _vn;
    int size;

    Face();
    ~Face() {

    }
    void clear() {
        if (_v)
            delete _v;
        //if (_vn)
        //    delete _vn;
    }
    void add(unsigned int v);
    //void add(unsigned int v, unsigned int vn);
};

class ThreeD {
public:
    int _sizeCoord;
    int _sizeFace;
    int _sizeNorm;
    Coord* _coord;
    Face* _face;
    Norm* _norm;

    ThreeD(const char* filename, Image &im);
    ~ThreeD();

    void provSet(Image& image, Color3 color, double cof, double offsetX, double offsetY, double fi=0.0, double psi=0., double nu=0.);
    void polSet(Image& image, Color3 color, double cof, double offsetX, double offsetY, double fi=0, double psi=0, double nu=0);
    void triangle(Face face, Image& image, Color3 color, double cof, double offsetX, double offsetY, int* z_buf, double fi=0);

};