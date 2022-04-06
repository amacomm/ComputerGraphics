#include "Structers.h"

Coord::Coord(float x, float y, float z) :_x(x), _y(y), _z(z) {};

TexturaCoord::TexturaCoord(float x, float y) :_x(x), _y(y) {};

Norm::Norm(double x, double y, double z) :_x(x), _y(y), _z(z) {};

Norm Norm::operator+= (Norm const n) {
    double length1 = std::sqrt(std::pow(n._x, 2) + std::pow(n._y, 2) + std::pow(n._z, 2));
    double length2 = std::sqrt(std::pow(_x, 2) + std::pow(_y, 2) + std::pow(_z, 2));
    double ccos = n._x * _x + n._y * _y + n._z * _z;
    ccos /= length1 * length2 > 0 ? length2 : 1;
    double  x = -std::sqrt(std::pow(n._x, 2) + std::pow(_x, 2) + 2 * abs(n._x) * abs(_x) * ccos),
            y = -std::sqrt(std::pow(n._y, 2) + std::pow(_y, 2) + 2 * abs(n._y) * abs(_y) * ccos),
            z = -std::sqrt(std::pow(n._z, 2) + std::pow(_z, 2) + 2 * abs(n._z) * abs(_z) * ccos);
    double length = std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
    _x = x / length; _y = y / length; _z = z / length;
    return *this;
}

Face::Face() {
    _v = nullptr;
    _vn = nullptr;
    _vt = nullptr;
    size = 0;
}

void Face::clear() {
    if (_v)
        delete _v;
    if (_vn)
        delete _vn;
    if (_vt)
        delete _vt;
}

void Face::add(unsigned int v, unsigned int vn, unsigned int vt) {
    unsigned int* newV = new unsigned int[++size];
    unsigned int* newVn = new unsigned int[size];
    unsigned int* newVt = new unsigned int[size];
    for (int i = 0; i < size - 1; i++) {
        newV[i] = _v[i];
        newVn[i] = _vn[i];
        newVt[i] = _vt[i];
    }
    newV[size - 1] = v;
    newVn[size - 1] = vn;
    newVt[size - 1] = vt;
    if (_v) {
        delete[] _v;
        delete[] _vn;
        delete[] _vt;
    }
    _v = newV;
    _vn = newVn;
    _vt = newVt;
}

Triangle::Triangle(Coord* coord1, Coord* coord2, Coord* coord3, Norm norm1, Norm norm2, Norm norm3) : _coord1(coord1), _coord2(coord2), _coord3(coord3), _norm1(norm1), _norm2(norm2), _norm3(norm3),
_tcoord1(TexturaCoord(0.1f, 0.1f)), _tcoord2(TexturaCoord(0.1f, 0.9f)), _tcoord3(TexturaCoord(0.9f, 0.9f))
{
    this->PoligonNorm();
}

void Triangle::PoligonNorm() {
    double n1[3] = { _coord2->_x - _coord1->_x, _coord2->_y - _coord1->_y, _coord2->_z - _coord1->_z };
    double n2[3] = { _coord2->_x - _coord3->_x, _coord2->_y - _coord3->_y, _coord2->_z - _coord3->_z };
    double n[3] = { n1[1] * n2[2] - n1[2] * n2[1], n1[0] * n2[2] - n1[2] * n2[0] ,n1[0] * n2[1] - n1[1] * n2[0] };
    double length = std::sqrt(std::pow(n[0], 2) + std::pow(n[1], 2) + std::pow(n[2], 2));
    n[0] /= length; n[1] /= length; n[2] /= length;
    _norm1._x = -n[0]; _norm1._y = -n[1]; _norm1._z = -n[2];
    _norm2._x = -n[0]; _norm2._y = -n[1]; _norm2._z = -n[2];
    _norm3._x = -n[0]; _norm3._y = -n[1]; _norm3._z = -n[2];
}