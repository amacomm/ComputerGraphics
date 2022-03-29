#pragma once
#include "Image.h"
#include <cmath>

class Coord {
public:
    float _x, _y, _z;
    Coord(float x=0, float y=0, float z=0);
    //Coord();
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
class Zbuff {
public:

    double* z_buf;
    int width, height;
    Zbuff(int height, int width):height(height), width(width){
        z_buf = new double[height * width];
        for (int i = 0; i < width * height; z_buf[i++] = 200000000);
    }
    ~Zbuff() {
        delete[] z_buf;
    }
    bool ifSet(double z, int i, int j) {
        if (z <= z_buf[width * i + j]) {
            z_buf[width * i + j] = z;
            return true;
        }
        return false;
    }
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
    ThreeD();
    ~ThreeD();

    void provSet(Image& image, Color3 color);
    void polSet(Image& image, Color3 color);
    void triangle(Face face, Image& image, Color3 color, Zbuff& z_buf);
    void toPerspectiv(double ax, double ay, int u0, int v0) {
        double zn = 1, zf =100;
        for (int i = 0; i < _sizeCoord; ++i) {

            _coord[i]._x = (_coord[i]._x * ax) / _coord[i]._z + u0;
            _coord[i]._y = (_coord[i]._y * ay) / _coord[i]._z + v0;
           // _coord[i]._z = (zf / (zf - zn)) * (1 - zn / _coord[i]._z);
        }
    }
    void toOrdinary(double ax, double ay, double az, int u0, int v0) {
        for (int i = 0; i < _sizeCoord; ++i) {
            _coord[i]._x = (_coord[i]._x * ax) + u0;
            _coord[i]._y = (_coord[i]._y * ay)  + v0;
            _coord[i]._z =  _coord[i]._z*az ;
        }
    }
    void MoveTo(double x = 0, double y = 0, double z = 0) {
        for (int i = 0; i < _sizeCoord; ++i) {
            _coord[i]._x += x;
            _coord[i]._y += y;
            _coord[i]._z += z;
        }
    }
    void MoveTo(Coord coord) {
        MoveTo(coord._x, coord._y, coord._z);
    }
    void toTurn(double a, double b, double c) {
        for (int i = 0; i < _sizeCoord; ++i) {
            _coord[i]._x = cos(c)*cos(b)* _coord[i]._x+sin(c)*cos(b)* _coord[i]._y+sin(b)* _coord[i]._z;
            _coord[i]._y = (-sin(a)*sin(b)*cos(c)-sin(c)*cos(a))* _coord[i]._x+(-sin(a)*sin(b)*sin(c)+cos(a)*cos(c))* _coord[i]._y+sin(a)*cos(b)* _coord[i]._z;
            _coord[i]._z = (sin(a)*sin(c)-sin(b)*cos(c)*cos(a))* _coord[i]._x+(-sin(b)*cos(a)*sin(c)-sin(a)*cos(c))* _coord[i]._y+cos(a)*cos(b)* _coord[i]._z;
        }
    }
};