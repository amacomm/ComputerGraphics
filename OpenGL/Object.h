#pragma once
#include "Image.h"
#include <cmath>

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

    ThreeD(const char* filename);
    ~ThreeD();

    void provSet(Image& image, Color3 color, double cof, double offsetX, double offsetY, double fi=0.0, double psi=0., double nu=0.);
    void polSet(Image& image, Color3 color);
    void triangle(Face face, Image& image, Color3 color, int* z_buf);
    void toDisplayCord(double ax, double ay, int u0, int v0, double tx=0, double ty = 0, double tz = 20000) {
        double zn = 1, zf = 100;
        for (int i = 0; i < _sizeCoord; ++i) {
            _coord[i]._x += tx;
            _coord[i]._y += ty;
            _coord[i]._z += tz;
            _coord[i]._x = (_coord[i]._x * ax) / _coord[i]._z + u0;
            _coord[i]._y = (_coord[i]._y * ay) / _coord[i]._z + v0;
            _coord[i]._z = (zf/(zf-zn))*(1-zn/ _coord[i]._z) ;
        }
    }
    void toTurn(double a, double b, double c) {
        for (int i = 0; i < _sizeCoord; ++i) {
            _coord[i]._x = cos(c)*cos(b)* _coord[i]._x+sin(c)*cos(b)* _coord[i]._y+sin(b)* _coord[i]._z;
            _coord[i]._y = (-sin(a)*sin(b)*cos(c)-sin(c)*cos(a))* _coord[i]._x+(-sin(a)*sin(b)*sin(c)+cos(a)*cos(c))* _coord[i]._y+sin(a)*cos(b)* _coord[i]._z;
            _coord[i]._z = (sin(a)*sin(c)-sin(b)*cos(c)*cos(a))* _coord[i]._x+(-sin(b)*cos(a)*sin(c)-sin(a)*cos(c))* _coord[i]._y+cos(a)*cos(b)* _coord[i]._z;
        }
    }
};