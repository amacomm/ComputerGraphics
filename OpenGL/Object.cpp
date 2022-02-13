#include "Object.h"
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>

Coord::Coord(double x = 0, double y = 0, double z = 0) :_x(x), _y(y), _z(z) {};

Face::Face(unsigned int v1 = 0, unsigned int v2 = 0, unsigned int v3 = 0, unsigned int v4 = 0){
    _v[0] = v1;
    _v[1] = v2;
    _v[2] = v3;
    _v[3] = v4;
}

ThreeD::ThreeD(const char* filename) :_sizeCoord(0), _sizeFace(0) {
    //std::string s1, s2, s3;
    char ch[100];
    std::ifstream fin(filename);
    if (!fin)
        return;
    while (!fin.eof())
    {
        fin >> ch;
        if (ch[0] == 'v' && ch[1] == '\0')
        {
            Coord* newCoord = new Coord[++_sizeCoord];
            fin >> newCoord[_sizeCoord - 1]._x >> newCoord[_sizeCoord - 1]._y >> newCoord[_sizeCoord - 1]._z;
            for (int i = 0; i < _sizeCoord - 1; ++i)
                newCoord[i] = _coord[i];
            if (!_coord)
                delete[] _coord;
            _coord = newCoord;
        }
        else if (ch[0] == 'f' && ch[1] == '\0')
        {
            Face* newFace = new Face[++_sizeFace];
            std::string t;
            getline(fin, t);
            char shum[100];
            //sscanf(t.c_str(), " %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i", &newFace[_sizeFace - 1]._v[0], &shum, &shum, &newFace[_sizeFace - 1]._v[1], &shum, &shum, &newFace[_sizeFace - 1]._v[2], &shum, &shum, &newFace[_sizeFace - 1]._v[3], &shum, &shum);
            //sscanf(t.c_str(), " %i/%i %i/%i %i/%i %i/%i", &newFace[_sizeFace - 1]._v[0], &shum, &newFace[_sizeFace - 1]._v[1], &shum, &newFace[_sizeFace - 1]._v[2], &shum, &newFace[_sizeFace - 1]._v[3], &shum);
            sscanf(t.c_str(), " %i%[^ ] %i%[^ ] %i%[^ ] %i", &newFace[_sizeFace - 1]._v[0] ,&shum, &newFace[_sizeFace - 1]._v[1] ,&shum, &newFace[_sizeFace - 1]._v[2], &shum, & newFace[_sizeFace - 1]._v[3]);
            for (int i = 0; i < _sizeFace - 1; ++i)
                newFace[i] = _face[i];
            if (!_face)
                delete[] _face;
            _face = newFace;
        }
    }
}

ThreeD::~ThreeD() {
    delete[] _coord;
    delete[] _face;
}

void ThreeD::provSet(Image& image, Color3 color, double cof, double offsetX, double offsetY, double fi, double psi, double nu) {
    for (int i = 0; i < _sizeFace; i++)
    {
        Face face(_face[i]);
        int ch = (face._v[3] == 0 ? 3 : 4);
        for (int j = 0; j < ch; j++)
            image.line(cof * (_coord[face._v[j] - 1]._x* cos(fi) + _coord[face._v[j] - 1]._z* sin(fi)) + offsetX, cof * (_coord[face._v[j] - 1]._y * cos(nu) + _coord[face._v[j] - 1]._z * sin(nu)) + offsetY,
                cof *( _coord[face._v[(j + 1) % ch] - 1]._x * cos(fi) + _coord[face._v[(j + 1) % ch] - 1]._z * sin(fi)) + offsetX, cof * (_coord[face._v[(j + 1) % ch] - 1]._y * cos(nu) + _coord[face._v[(j + 1) % ch] - 1]._z * sin(nu)) + offsetY, color);
    }
}

void ThreeD::triangle(Face face, Image& image, Color3 color1, double cof, double offsetX, double offsetY, double* z_buf) {
    int ch = (face._v[3] == 0 ? 1 : 0);
    double x[4], y[4], z[4];
    for (int i = 0; i < 4; i++)
    {
        x[i] = _coord[face._v[i] - 1]._x;
        y[i] = _coord[face._v[i] - 1]._y;
        z[i] = _coord[face._v[i] - 1]._z;
    }

    double n1[3] = { x[1] - x[0],y[1] - y[0], z[1] - z[0] };
    double n2[3] = { x[1] - x[2],y[1] - y[2], z[1] - z[2] };
    double n[3] = {n1[1]*n2[2]- n1[2] * n2[1], n1[0] * n2[2] - n1[2] * n2[0] ,n1[0] * n2[1] - n1[1] * n2[0] };
    double length = std::sqrt(std::pow(n[0],2)+ std::pow(n[1], 2)+ std::pow(n[2], 2));
    //n[0] /= length; n[1] /= length; n[1] /= length;
    double l[3] = { 0,0,1 };
    double lengthL = std::sqrt(std::pow(l[0], 2) + std::pow(l[1], 2) + std::pow(l[2], 2));
    double s = n[0] * l[0] + n[1] * l[1] + n[2] *l[2];
    s /= length * lengthL;
    if (s >= 0)
        return;

    Color3 color(-255 * s, 0, 0);

    for (int i = 0; i < 4; i++)
    {
        x[i] = cof * x[i] + offsetX;
        y[i] = cof * y[i] + offsetY;
        z[i] = cof * z[i] + offsetX;
    }

    double xmin = *std::min_element(std::begin(x), std::end(x)-ch);
    double ymin = *std::min_element(std::begin(y), std::end(y)-ch);
    double xmax = *std::max_element(std::begin(x), std::end(x)-ch);
    double ymax = *std::max_element(std::begin(y), std::end(y)-ch);

    xmin = xmin > 0 ? xmin : 0;
    ymin = ymin > 0 ? ymin : 0;
    xmax = xmax < image.width() ? xmax : image.width();
    ymax = ymax < image.height() ? ymax : image.height();
    double lambda[4];
    lambda[3] = 1;
    for (int i = xmin; i < xmax; i++)
        for (int j = ymin; j < ymax; j++)
        {
            for (int k = 0; k < 4-ch; k++)
            {
                int k1 = k % (4-ch), k2 = (k + 1) % (4 - ch), k0 = (k - 1) % (4 - ch) < 0 ? (k - 1) % (4 - ch) + (4 - ch) : (k - 1) % (4 - ch);
                lambda[k] = ((x[k] - x[k2]) * (j - y[k2]) - (y[k1] - y[k2]) * (i - x[k2])) / ((x[k1] - x[k2]) * (y[k0] - y[k2]) - (y[k1] - y[k2]) * (x[k0] - x[k2]));
            }
            if (lambda[0]>0 && lambda[1]>0 && lambda[2]>0 && lambda[3]>0) {
                double z0 = z[0] * lambda[0] * z[1] * lambda[2] * z[2] * lambda[2] * ch == 0 ? z[3] * lambda[3]:1;
                if (z0 < z_buf[image.width() * i + j]) {
                    image.set(i, j, color);
                    z_buf[image.width() * i + j] = z0;
                }
            }
        }
}

void ThreeD::polSet(Image& image, Color3 color, double cof, double offsetX, double offsetY, double fi, double psi, double nu) {
    std::srand(std::time(nullptr));
    double* z_buf = new double[image.width() * image.height()];
    for (int i = 0; i < image.width() * image.height(); z_buf[i++] = 1.7976931348623158e+308);
    for (int i = 0; i < _sizeFace; i++)
    {
        Color3 c(std::rand()%256, std::rand() % 256, std::rand() % 256);
        triangle(_face[i], image, c, cof, offsetX, offsetY, z_buf);
    }
    delete[] z_buf;
}