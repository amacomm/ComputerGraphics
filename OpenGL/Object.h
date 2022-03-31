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
    Norm(double x=0, double y=0, double z=0);
    ~Norm() {};
    void Normalize(Norm n) {
        double length1 = std::sqrt(std::pow(n._x, 2) + std::pow(n._y, 2) + std::pow(n._z, 2));
        double length2 = std::sqrt(std::pow(_x, 2) + std::pow(_y, 2) + std::pow(_z, 2));
        double ccos = n._x * _x + n._y * _y + n._z * _z;
        ccos /= length1 * length2>0? length2:1;
        double  x= std::sqrt(std::pow(n._x, 2) + std::pow(_x, 2) + 2 * abs(n._x) * abs(_x) * ccos),
                y= std::sqrt(std::pow(n._y, 2) + std::pow(_y, 2) + 2 * abs(n._y) * abs(_y) * ccos),
                z= std::sqrt(std::pow(n._z, 2) + std::pow(_z, 2) + 2 * abs(n._z) * abs(_z) * ccos);
        double length = std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
        _x=x / length; _y=y / length; _z= z / length;
    }
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

class Triangle {
public:
    Coord *_coord1, *_coord2, *_coord3;
    Norm _norm1, _norm2, _norm3;
    Triangle() {}
    Triangle(Coord *coord1 , Coord *coord2 , Coord *coord3 /*, Norm norm1, Norm norm2, Norm norm3*/) : _coord1(coord1), _coord2(coord2), _coord3(coord3), _norm1(Norm()), _norm2(Norm()), _norm3(Norm()) {
        this->PoligonNorm();
    }
    ~Triangle() {}
    void PoligonNorm() {
        double n1[3] = { _coord2->_x - _coord1->_x, _coord2->_y - _coord1->_y, _coord2->_z - _coord1->_z };
        double n2[3] = { _coord2->_x - _coord3->_x, _coord2->_y - _coord3->_y, _coord2->_z - _coord3->_z };
        double n[3] = { n1[1] * n2[2] - n1[2] * n2[1], n1[0] * n2[2] - n1[2] * n2[0] ,n1[0] * n2[1] - n1[1] * n2[0] };
        double length = std::sqrt(std::pow(n[0], 2) + std::pow(n[1], 2) + std::pow(n[2], 2));
        n[0] /= length; n[1] /= length; n[2] /= length;
        _norm1._x = n[0]; _norm1._y = n[1]; _norm1._z = n[2];
        _norm2._x = n[0]; _norm2._y = n[1]; _norm2._z = n[2];
        _norm3._x = n[0]; _norm3._y = n[1]; _norm3._z = n[2];
    }
};


class ThreeD {
public:
    int _sizeCoord;
    int _sizeFace;
    int _sizeNorm;
    double x_max, y_max, z_max;
    Coord* _coord;
    Face* _face;
    Norm* _norm;
    Triangle* _tri;

    ThreeD(const char* filename);
    ThreeD();
    ~ThreeD();

    void provSet(Image& image, Color3 color);
    void polSet(Image& image, Color3 color);
    void triangle(Triangle tri, Image& image, Color3 color);
    //void triangle(Face face, Image& image, Color3 color);
    void toPerspectiv(double ax, double ay, int u0, int v0) {
        double zn = 1, zf =100;
        for (int i = 0; i < _sizeCoord; ++i) {

            _coord[i]._x = (_coord[i]._x * ax) / _coord[i]._z + u0;
            _coord[i]._y = (_coord[i]._y * ay) / _coord[i]._z + v0;
            _coord[i]._z = (zf / (zf - zn)) * (1 - zn / _coord[i]._z);
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
    void Norm() {
        x_max = y_max = z_max = 0;
        for (int i = 0; i < _sizeCoord; ++i) {
            x_max = abs(_coord[i]._x) > x_max ? abs(_coord[i]._x) : x_max;
            y_max = abs(_coord[i]._y) > y_max ? abs(_coord[i]._y) : y_max;
            z_max = abs(_coord[i]._z) > z_max ? abs(_coord[i]._z) : z_max;
        }
        for (int i = 0; i < _sizeCoord; ++i) {
            _coord[i]._x /= x_max;
            _coord[i]._y /= y_max;
            _coord[i]._z /= z_max;
        }
    }
    void PreNorm() {
        for (int i = 0; i < _sizeFace; ++i) {
            _tri[i].PoligonNorm();
        }
    }
    void Smooth() {
        for (int i = 0; i < _sizeCoord; i++){
            ::Norm n = ::Norm();
            for (int j = 0; j < _sizeFace; ++j) {
                if (_tri[j]._coord1==&_coord[i])
                {
                    n.Normalize(_tri[j]._norm1);
                }
                else if (_tri[j]._coord2 == &_coord[i])
                {
                    n.Normalize(_tri[j]._norm2);
                }
                else if (_tri[j]._coord3 == &_coord[i])
                {
                    n.Normalize(_tri[j]._norm3);
                }
            }
            for (int j = 0; j < _sizeFace; ++j) {
                if (_tri[j]._coord1 == &_coord[i])
                {
                    _tri[j]._norm1 = n;
                }
                else if (_tri[j]._coord2 == &_coord[i])
                {
                    _tri[j]._norm2 = n;
                }
                else if (_tri[j]._coord3 == &_coord[i])
                {
                    _tri[j]._norm3 = n;

                }
            }
        }
    }
};