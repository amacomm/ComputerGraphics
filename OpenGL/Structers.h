#pragma once
#include <cmath>

class Coord {
public:
    float _x, _y, _z;
    Coord(float x = 0, float y = 0, float z = 0);
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
    Norm(double x = 0, double y = 0, double z = 0);
    ~Norm() {};
    Norm operator+= (Norm const n);
    const Norm &operator- () {
        return Norm(-_x, -_y, -_z);
    }
};

class Face {
public:
    unsigned int* _v;
    unsigned int* _vn;
    unsigned int* _vt;
    int size;

    Face();
    ~Face() {}
    void clear();
    void add(unsigned int v, unsigned int vn, unsigned int vt);
};

class Triangle {
public:
    Coord* _coord1, * _coord2, * _coord3;
    Norm _norm1, _norm2, _norm3;
    TexturaCoord _tcoord1, _tcoord2, _tcoord3;
    Triangle() {}
    Triangle(Coord* coord1, Coord* coord2, Coord* coord3, Norm norm1 = Norm(), Norm norm2 = Norm(), Norm norm3 = Norm());
    ~Triangle() {}
    void PoligonNorm();
};