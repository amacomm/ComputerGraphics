#pragma once
#include "Image.h"
#include <cmath>

class Coord {
public:
    float _x, _y, _z;
    Coord(float x=0, float y=0, float z=0);
    ~Coord() {};
};

class TexturaCoord {
public:
    float _x, _y;
    TexturaCoord(float x = 0, float y = 0);
    ~TexturaCoord() {};
};

class Norm {
public:
    double _x, _y, _z;
    Norm(double x=0, double y=0, double z=0);
    ~Norm() {};
    Norm operator+= (Norm const n);
};

class Face {
public:
    unsigned int* _v;
    unsigned int* _vn;
    unsigned int* _vt;
    int size;

    Face();
    ~Face(){}
    void clear();
    void add(unsigned int v, unsigned int vn, unsigned int vt);
};

class Triangle {
public:
    Coord *_coord1, *_coord2, *_coord3;
    Norm _norm1, _norm2, _norm3;
    TexturaCoord _tcoord1, _tcoord2, _tcoord3;
    Triangle() {}
    Triangle(Coord* coord1, Coord* coord2, Coord* coord3, Norm norm1 = Norm(), Norm norm2 = Norm(), Norm norm3 = Norm());
    ~Triangle() {}
    void PoligonNorm();
};


class ThreeD {
    int _sizeCoord;
    int _sizeNorm;
    int _sizeText;
    int _sizeTri;
    Coord* _coord;
    TexturaCoord* _textCoord;
    Norm* _norm;
    Triangle* _tri;
public:

    ThreeD(const char* filename);
    ThreeD();
    ~ThreeD();

    void provSet(Image& image, Color3 color);
    void polSet(Image& image, Image& text);
    void polSet(Image& image, Color3 color);
    void line(Image& image, int x0, int y0, int x1, int y1, Color3 color, float z0 = 0, float z1 = 0);
    void triangle(Triangle tri, Image& image, Image& text);
    void toPerspectiv(float ax, float ay, int u0=0, int v0=0);
    void toOrdinary(float ax, float ay, float az, int u0=0, int v0=0, float z0 = 0);
    void MoveTo(float x = 0, float y = 0, float z = 0);
    void MoveTo(Coord coord);
    void toTurn(float a, float b, float c);
    void Norm();
    void PreNorm();
    void Smooth();
};