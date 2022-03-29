#include "Object.h"
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <algorithm>

Coord::Coord(float x , float y, float z) :_x(x), _y(y), _z(z) {};
//Coord::Coord() :_x(0), _y(0), _z(0) {};

Norm::Norm(double x = 0, double y = 0, double z = 0) :_x(x), _y(y), _z(z) {};

Face::Face(){
    _v = nullptr;
    //_vn = new unsigned int[1];
    size = 0;
}

void Face::add(unsigned int v) {
    unsigned int* newV = new unsigned int[++size];
    //unsigned int* newVn = new unsigned int[size];
    for (int i = 0; i < size - 1; i++) {
        newV[i] = _v[i];
        //newVn[i] = _vn[i];
    }
    newV[size - 1] = v;
    //newVn[size - 1] = vn;
    if(_v!=nullptr)
        delete[] _v;
    //delete[] _vn;
    _v = newV;
    //_vn = newVn;
}

ThreeD::ThreeD(const char* filename) :_sizeCoord(0), _sizeFace(0), _sizeNorm(0) {
    char ch[100];
    std::ifstream fin(filename);
    if (!fin)
        return;
    int chislo = 0;
    //int* z_buf = new int[image.width() * image.height()];
    //for (int i = 0; i < image.width() * image.height(); z_buf[i++] = -2000000000);
    //Color3 c(255, 255, 255);
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
        //if (ch[0] == 'v' && ch[1] == 'n')
        //{
        //    Norm* newNorm = new Norm[++_sizeNorm];
        //    fin >> newNorm[_sizeNorm - 1]._x >> newNorm[_sizeNorm - 1]._y >> newNorm[_sizeNorm - 1]._z;
        //    for (int i = 0; i < _sizeNorm - 1; ++i)
        //        newNorm[i] = _norm[i];
        //    if (!_norm)
        //        delete[] _norm;
        //    _norm = newNorm;
        //}
        else if (ch[0] == 'f' && ch[1] == '\0')
        {
            //Face newFace;
            //std::string str;
            //getline(fin, str);
            //std::istringstream iss(str);
            //while (!iss.eof()) {
            //    int integer1, integer2, integer3;
            //    std::string s;
            //    iss >> s;
            //    if (s == "")
            //        continue;
            //    sscanf(s.c_str(), "%i/%i/%i", &integer1, &integer2, &integer3);
            //    newFace.add(integer1, integer3);
            //}
            //double cof = 20;
            //double fi = 3.14 / 4;
            //double psi = 0;
            //double nu = -3.14 / 8;
            //double offsetX = 500; 
            //double offsetY = 500;
            ////for (int j = 0; j < newFace.size; j++)
            ////image.line(cof * ((_coord[newFace._v[j] - 1]._x * cos(fi) + _coord[newFace._v[j] - 1]._z * sin(fi)) * cos(psi) + sin(-psi) * (_coord[newFace._v[j] - 1]._y * cos(nu) + _coord[newFace._v[j] - 1]._z * sin(nu))) + offsetX, cof * ((_coord[newFace._v[j] - 1]._y * cos(nu) + _coord[newFace._v[j] - 1]._z * sin(nu)) * cos(psi) + sin(psi) * (_coord[newFace._v[j] - 1]._x * cos(fi) + _coord[newFace._v[j] - 1]._z * sin(fi))) + offsetY,
            ////    cof * ((_coord[newFace._v[(j + 1) % newFace.size] - 1]._x * cos(fi) + _coord[newFace._v[(j + 1) % newFace.size] - 1]._z * sin(fi)) * cos(psi) + sin(-psi) * (_coord[newFace._v[(j + 1) % newFace.size] - 1]._y * cos(nu) + _coord[newFace._v[(j + 1) % newFace.size] - 1]._z * sin(nu))) + offsetX, cof * ((_coord[newFace._v[(j + 1) % newFace.size] - 1]._y * cos(nu) + _coord[newFace._v[(j + 1) % newFace.size] - 1]._z * sin(nu)) * cos(psi) + sin(psi) * (_coord[newFace._v[(j + 1) % newFace.size] - 1]._x * cos(fi) + _coord[newFace._v[(j + 1) % newFace.size] - 1]._z * sin(fi))) + offsetY, c);
            //triangle(newFace, image, c , 20, 500, 500, z_buf, 3.14/2);
            
            Face* newFace = new Face[++_sizeFace];
            std::string str;
            getline(fin, str);
            std::istringstream iss(str);
            while (!iss.eof()) {
                int integer1, integer2, integer3;
                std::string s;
                iss >> s;
                if (s == "")
                    continue;
                sscanf(s.c_str(), "%i/%i/%i", &integer1, &integer2,&integer3);
                newFace[_sizeFace - 1].add(integer1);
            }
            for (int i = 0; i < _sizeFace - 1; ++i) {
                newFace[i] = _face[i];
            }
            if (_face)
                delete[] _face;
            _face = newFace;
        }
    }
}
ThreeD::ThreeD() {

}

ThreeD::~ThreeD() {
    delete[] _coord;
    for (int i = 0; i < _sizeFace ; i++)
        _face[i].clear();
    delete[] _face;
}

void ThreeD::provSet(Image& image, Color3 color) {
    for (int i = 0; i < _sizeFace; i++)
    {
        Face face(_face[i]);
        for (int j = 0; j < face.size; j++)
            image.line(_coord[face._v[j] - 1]._x, _coord[face._v[j] - 1]._y, _coord[face._v[(j + 1) % face.size] - 1]._x, _coord[face._v[(j + 1) % face.size] - 1]._y, color);
    }
}

double max_elem(double* x, int size) {
    double max = x[0];
    for (int i = 1; i < size; i++) {
        max = x[i] > max ? x[i] : max;
    }
    return max;
}

double min_elem(double* x, int size) {
    double min = x[0];
    for (int i = 1; i < size; i++) {
        min = x[i] < min ? x[i] : min;
    }
    return min;
}

void ThreeD::triangle(Face face, Image& image, Color3 color, Zbuff& z_buf) {
    double* x = new double[face.size];
    double* y = new double[face.size];
    double* z = new double[face.size];
    for (int i = 0; i < face.size; i++)
    {
        x[i] = _coord[face._v[i] - 1]._x;
        y[i] = _coord[face._v[i] - 1]._y;
        z[i] = _coord[face._v[i] - 1]._z;
    }

    double n1[3] = { x[1] - x[0],y[1] - y[0], z[1] - z[0] };
    double n2[3] = { x[1] - x[2],y[1] - y[2], z[1] - z[2] };
    double n[3] = {n1[1]*n2[2]- n1[2] * n2[1], n1[0] * n2[2] - n1[2] * n2[0] ,n1[0] * n2[1] - n1[1] * n2[0] };
    double length = std::sqrt(std::pow(n[0],2)+ std::pow(n[1], 2)+ std::pow(n[2], 2));
    n[0] /= length; n[1] /= length; n[1] /= length;
    double l[3] = { 0,0,1 };
    double lengthL = std::sqrt(std::pow(l[0], 2) + std::pow(l[1], 2) + std::pow(l[2], 2));
    double s = n[0] * l[0] + n[1] * l[1] + n[2] *l[2];
    s /= length * lengthL;
    if (s <= 0) {
        delete[] x;
        delete[] y;
        delete[] z;
        return;
    }
    
    color.intensity(s);

    double xmin = min_elem(x, face.size);
    double ymin = min_elem(y, face.size);
    double xmax = max_elem(x, face.size);
    double ymax = max_elem(y, face.size);

    xmin = xmin > 0 ? xmin : 0;
    ymin = ymin > 0 ? ymin : 0;
    xmax = xmax < image.width() ? xmax : image.width();
    ymax = ymax < image.height() ? ymax : image.height();
    double lambda[3];
    for (int i = xmin; i < xmax; i++)
        for (int j = ymin; j < ymax; j++)
            for (int t = 0; t < face.size-2; t++)
            {
                int km[3]{ 0, 1+t, 2+t };
                double z0 = 0;
                bool l = true;
                for (int k = 0; k < 3; k++)
                {
                    int k1 = km[k % 3], k2 = km[(k + 1) % 3], k0 = km[(k - 1) % 3 < 0 ? (k - 1) % 3 + 3 : (k - 1) % 3];
                    lambda[k] = ((x[k1] - x[k2]) * (j - y[k2]) - (y[k1] - y[k2]) * (i - x[k2])) / ((x[k1] - x[k2]) * (y[k0] - y[k2]) - (y[k1] - y[k2]) * (x[k0] - x[k2]));
                    l = l && (lambda[k] > 0);
                    z0 += z[k1] * lambda[k];
                }
                if (l&& z_buf.ifSet(z0, i, j))
                    image.set(i, j, color);
            }
    delete[] x;
    delete[] y;
    delete[] z;
}

void ThreeD::polSet(Image& image, Color3 color) {
    Zbuff zbuff(image.height(), image.width());
    for (int i = 0; i < _sizeFace; i++)
        triangle(_face[i], image, color, zbuff);
}