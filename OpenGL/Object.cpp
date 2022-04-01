#include "Object.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

Coord::Coord(float x , float y, float z) :_x(x), _y(y), _z(z) {};

TexturaCoord::TexturaCoord(float x, float y) :_x(x), _y(y) {};

Norm::Norm(double x, double y, double z) :_x(x), _y(y), _z(z) {};

Norm Norm::operator+= (Norm const n) {
    double length1 = std::sqrt(std::pow(n._x, 2) + std::pow(n._y, 2) + std::pow(n._z, 2));
    double length2 = std::sqrt(std::pow(_x, 2) + std::pow(_y, 2) + std::pow(_z, 2));
    double ccos = n._x * _x + n._y * _y + n._z * _z;
    ccos /= length1 * length2 > 0 ? length2 : 1;
    double  x = std::sqrt(std::pow(n._x, 2) + std::pow(_x, 2) + 2 * abs(n._x) * abs(_x) * ccos),
        y = std::sqrt(std::pow(n._y, 2) + std::pow(_y, 2) + 2 * abs(n._y) * abs(_y) * ccos),
        z = std::sqrt(std::pow(n._z, 2) + std::pow(_z, 2) + 2 * abs(n._z) * abs(_z) * ccos);
    double length = std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
    _x = x / length; _y = y / length; _z = z / length;
    return *this;
}

Face::Face(){
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
    _norm1._x = n[0]; _norm1._y = n[1]; _norm1._z = n[2];
    _norm2._x = n[0]; _norm2._y = n[1]; _norm2._z = n[2];
    _norm3._x = n[0]; _norm3._y = n[1]; _norm3._z = n[2];
}

ThreeD::ThreeD(const char* filename) :_sizeCoord(0), _sizeText(0),  _sizeNorm(0), _sizeTri(0) {
    char ch[100];
    std::ifstream fin(filename);
    if (!fin)
        return;
    int chislo = 0;
    while (!fin.eof())
    {
        fin >> ch;
        if (ch[0] == 'v' && ch[1] == '\0')
        {
            Coord* newCoord = new Coord[++_sizeCoord];
            fin >> newCoord[_sizeCoord - 1]._x >> newCoord[_sizeCoord - 1]._y >> newCoord[_sizeCoord - 1]._z;
            for (int i = 0; i < _sizeCoord - 1; ++i)
                newCoord[i] = _coord[i];
            if (_coord)
                delete[] _coord;
            _coord = newCoord;
        }
        if (ch[0] == 'v' && ch[1] == 'n')
        {
            ::Norm* newNorm = new ::Norm[++_sizeNorm];
            fin >> newNorm[_sizeNorm - 1]._x >> newNorm[_sizeNorm - 1]._y >> newNorm[_sizeNorm - 1]._z;
            for (int i = 0; i < _sizeNorm - 1; ++i)
                newNorm[i] = _norm[i];
            if (_norm)
                delete[] _norm;
            _norm = newNorm;
        }
        if (ch[0] == 'v' && ch[1] == 't')
        {
            TexturaCoord* newText = new TexturaCoord[++_sizeText];
            fin >> newText[_sizeText - 1]._x >> newText[_sizeText - 1]._y;
            for (int i = 0; i < _sizeText - 1; ++i)
                newText[i] = _textCoord[i];
            if (_textCoord)
                delete[] _textCoord;
            _textCoord = newText;
        }
        else if (ch[0] == 'f' && ch[1] == '\0')
        {
            std::string str;
            getline(fin, str);
            std::istringstream iss(str);
            Face face;
            while (!iss.eof()) {
                int integer1, integer2, integer3;
                std::string s;
                iss >> s;
                if (s == "")
                    continue;
                sscanf(s.c_str(), "%i/%i/%i", &integer1, &integer2,&integer3);
                face.add(integer1-1, integer3-1, integer2-1);
            }
            for (int t = 0; t < face.size - 2; t++)
            {
                Triangle* newTri = new Triangle[++_sizeTri];
                int km[3]{ 0, 1 + t, 2 + t };
                newTri[_sizeTri - 1] = Triangle(&_coord[face._v[km[0]]], &_coord[face._v[km[1]]], &_coord[face._v[km[2]]]);
                if (_sizeNorm > 0) {
                    newTri[_sizeTri - 1]._norm1 = _norm[face._vn[km[0]]];
                    newTri[_sizeTri - 1]._norm2 = _norm[face._vn[km[1]]];
                    newTri[_sizeTri - 1]._norm3 = _norm[face._vn[km[2]]];
                }
                if (_sizeCoord > 0) {
                    newTri[_sizeTri - 1]._tcoord1 = _textCoord[face._vt[km[0]]];
                    newTri[_sizeTri - 1]._tcoord2 = _textCoord[face._vt[km[1]]];
                    newTri[_sizeTri - 1]._tcoord3 = _textCoord[face._vt[km[2]]];
                }
                for (int i = 0; i < _sizeTri - 1; ++i)
                    newTri[i] = _tri[i];
                if (_tri)
                    delete[] _tri;
                _tri = newTri;

            }
        }
    }
}
ThreeD::ThreeD() {

}

ThreeD::~ThreeD() {
    delete[] _coord;
    delete[] _norm;
    delete[] _textCoord;
    delete[] _tri;
}

void ThreeD::provSet(Image& image, Color3 color) {
    for (int i = 0; i < _sizeTri; i++)
    {
        line(image, _tri[i]._coord1->_x, _tri[i]._coord1->_y, _tri[i]._coord2->_x, _tri[i]._coord2->_y, color, _tri[i]._coord1->_z, _tri[i]._coord2->_z);
        line(image, _tri[i]._coord2->_x, _tri[i]._coord2->_y, _tri[i]._coord3->_x, _tri[i]._coord3->_y, color, _tri[i]._coord2->_z, _tri[i]._coord3->_z);
        line(image, _tri[i]._coord3->_x, _tri[i]._coord3->_y, _tri[i]._coord1->_x, _tri[i]._coord1->_y, color, _tri[i]._coord3->_z, _tri[i]._coord1->_z);
    }
}

float max_elem(float* x, int size) {
    float max = x[0];
    for (int i = 1; i < size; i++) {
        max = x[i] > max ? x[i] : max;
    }
    return max;
}

float min_elem(float* x, int size) {
    float min = x[0];
    for (int i = 1; i < size; i++) {
        min = x[i] < min ? x[i] : min;
    }
    return min;
}
void ThreeD::triangle(Triangle tri, Image& image, Image& text) {
    float x[3];
    float y[3];
    float z[3];
    float xt[3];
    float yt[3];
    x[0] = tri._coord1->_x; y[0] = tri._coord1->_y; z[0] = tri._coord1->_z;
    x[1] = tri._coord2->_x; y[1] = tri._coord2->_y; z[1] = tri._coord2->_z;
    x[2] = tri._coord3->_x; y[2] = tri._coord3->_y; z[2] = tri._coord3->_z;
    xt[1] = tri._tcoord1._x; yt[1] = tri._tcoord1._y;
    xt[2] = tri._tcoord2._x; yt[2] = tri._tcoord2._y;
    xt[0] = tri._tcoord3._x; yt[0] = tri._tcoord3._y;

    double nx[3] = { tri._norm3._x,tri._norm1._x, tri._norm2._x , };
    double ny[3] = { tri._norm3._y,tri._norm1._y, tri._norm2._y , };
    double nz[3] = { tri._norm3._z,tri._norm1._z, tri._norm2._z , };


    float xmin = min_elem(x, 3);
    float ymin = min_elem(y, 3);
    float xmax = max_elem(x, 3);
    float ymax = max_elem(y, 3);

    xmin = xmin > 0 ? xmin : 0;
    ymin = ymin > 0 ? ymin : 0;
    xmax = xmax < image.width() ? xmax : image.width();
    ymax = ymax < image.height() ? ymax : image.height();
    double lambda[3];
    for (int i = (int)xmin; i < xmax; i++)
		for (int j = (int)ymin; j < ymax; j++)
		{
			double z0, xn, yn, zn, xc, yc;
			z0 = xn = yn = zn=xc=yc = 0;
			bool l = true;
			for (int k = 0; k < 3; k++)
			{
				int k1 = k % 3, k2 = (k + 1) % 3, k0 = (k - 1) % 3 < 0 ? (k - 1) % 3 + 3 : (k - 1) % 3;
				lambda[k] = ((x[k1] - x[k2]) * (j - y[k2]) - (y[k1] - y[k2]) * (i - x[k2])) / ((x[k1] - x[k2]) * (y[k0] - y[k2]) - (y[k1] - y[k2]) * (x[k0] - x[k2]));
				l = l && (lambda[k] > 0);
				z0 += z[k1] * lambda[k];
				xn += nx[k] * lambda[k];
				yn += ny[k] * lambda[k];
                zn += nz[k] * lambda[k];
                xc += xt[k] * lambda[k];
                yc += yt[k] * lambda[k];
			}
			if (l && image.ZbuffIfSet(z0, i, j)) {
				double l[3] = { 0,0,1 };
				double lengthL = std::sqrt(std::pow(l[0], 2) + std::pow(l[1], 2) + std::pow(l[2], 2));
				double s = xn * l[0] + yn * l[1] + zn * l[2];
				//double length = std::sqrt(std::pow(xn, 2) + std::pow(yn, 2) + std::pow(zn, 2));
				//s /= length * lengthL;
				if (s <= 0) return;

				Color3 c = text.get((int)(xc*text.width()),(int)(yc * text.height()));
                c = c.intensity(s);
				image.set(i, j, c);
			}
		}
}

void ThreeD::polSet(Image& image, Image& text) {
    for (int i = 0; i < _sizeTri; i++)
        triangle(_tri[i], image, text);
}

void ThreeD::polSet(Image& image, Color3 color) {
    Image im(50, 50, color);
    polSet(image, im);
}
void ThreeD::line(Image& image, int x0, int y0, int x1, int y1, Color3 color, float z0, float z1) {
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) { 
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    if (z0 > z1)
        std::swap(z0, z1);
    int dx = x1 - x0;
    int dy = y1 - y0;
    float derror = std::abs(dy / float(dx));
    float error = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (!(x < 0 || x >= image.width() || y < 0 || y >= image.height()))
        {
            if (steep) {
                if(image.ZbuffIfSet(z0/z1*dx*(x-x0)/x, y, x))
                image.set(y, x, color);
            }
            else {
                if(image.ZbuffIfSet(z0 / z1 * dx*(x - x0)/x, x, y))
                image.set(x, y, color);
            }
        }
        error += derror;
        if (error > .5) {
            y += (y1 > y0 ? 1 : -1);
            error -= 1.;
        }
    }
}

void ThreeD::toPerspectiv(float ax, float ay, int u0, int v0) {
    float zn = 1, zf = 100;
    for (int i = 0; i < _sizeCoord; ++i) {

        _coord[i]._x = (_coord[i]._x * ax) / _coord[i]._z + u0;
        _coord[i]._y = (_coord[i]._y * ay) / _coord[i]._z + v0;
        _coord[i]._z = (zf / (zf - zn)) * (1 - zn / _coord[i]._z);
    }
}

void ThreeD::toOrdinary(float ax, float ay, float az, int u0, int v0, float z0) {
    for (int i = 0; i < _sizeCoord; ++i) {
        _coord[i]._x = _coord[i]._x * ax + u0;
        _coord[i]._y = _coord[i]._y * ay + v0;
        _coord[i]._z = _coord[i]._z * az + z0;
    }
}

void ThreeD::MoveTo(float x, float y, float z) {
    for (int i = 0; i < _sizeCoord; ++i) {
        _coord[i]._x += x;
        _coord[i]._y += y;
        _coord[i]._z += z;
    }
}

void ThreeD::toTurn(float a, float b, float c) {
    for (int i = 0; i < _sizeCoord; ++i) {
        _coord[i]._x = cos(c) * cos(b) * _coord[i]._x + sin(c) * cos(b) * _coord[i]._y + sin(b) * _coord[i]._z;
        _coord[i]._y = (-sin(a) * sin(b) * cos(c) - sin(c) * cos(a)) * _coord[i]._x + (-sin(a) * sin(b) * sin(c) + cos(a) * cos(c)) * _coord[i]._y + sin(a) * cos(b) * _coord[i]._z;
        _coord[i]._z = (sin(a) * sin(c) - sin(b) * cos(c) * cos(a)) * _coord[i]._x + (-sin(b) * cos(a) * sin(c) - sin(a) * cos(c)) * _coord[i]._y + cos(a) * cos(b) * _coord[i]._z;
    }
}
void ThreeD::MoveTo(Coord coord) {
    MoveTo(coord._x, coord._y, coord._z);
}

void ThreeD::Norm() {
    float x_max, y_max, z_max;
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

void ThreeD::PreNorm() {
    for (int i = 0; i < _sizeTri; ++i)
        _tri[i].PoligonNorm();
}

void ThreeD::Smooth() {
    for (int i = 0; i < _sizeCoord; i++) {
        ::Norm n = ::Norm();
        for (int j = 0; j < _sizeTri; ++j) {
            if (_tri[j]._coord1 == &_coord[i])
            {
                n += _tri[j]._norm1;
            }
            else if (_tri[j]._coord2 == &_coord[i])
            {
                n += _tri[j]._norm2;
            }
            else if (_tri[j]._coord3 == &_coord[i])
            {
                n += _tri[j]._norm3;
            }
        }
        for (int j = 0; j < _sizeTri; ++j) {
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