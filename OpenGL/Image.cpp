#include "Image.h"
#include "BMP.h"
#include <windows.h>
#include <iostream>
#include <omp.h>

Color3::Color3(int r = 0, int g = 0, int b = 0) :
    _r(r), _g(g), _b(b) {};

Color3 Color3::intensity(float proc) {
    Color3 c(_r * proc, _g * proc, _b * proc);
    return c;
}

Zbuff::Zbuff(int height, int width) :height(height), width(width) {
    z_buf = new double[height * width];
    for (int i = 0; i < width * height; z_buf[i++] = 200000000);
}
Zbuff::~Zbuff() {
    delete[] z_buf;
}
bool Zbuff::ifSet(double z, int i, int j) {
    if (z <= z_buf[width * i + j]) {
        z_buf[width * i + j] = z;
        return true;
    }
    return false;
}

Image::Image(int width, int height, Color3 color) :
    _width(width), _height(height), _image(new unsigned char[_height * _width * 3]), z_buff(Zbuff(height, width)) {
    for (int i = 0; i < _width; i++)
        for (int j = 0; j < _height; j++)
            set(j, i, color);
};
Image::Image(char* filename) {
    _image = BMP24_read(_height, _width, filename);
}

int Image::width() const { return _width; }
int Image::height() const { return _height; }

void Image::set(int y, int x, const Color3& value) {
    _image[(_width * x + y) * 3 + 2] = (unsigned char)(value._r);///red
    _image[(_width * x + y) * 3 + 1] = (unsigned char)(value._g);///green
    _image[(_width * x + y) * 3 + 0] = (unsigned char)(value._b); ///blue
}
const Color3& Image::get(int y, int x) const {
    return Color3(_image[(_width * x + y) * 3 + 2], _image[(_width * x + y) * 3 + 1], _image[(_width * x + y) * 3 + 0]);
}

void Image::save(char* filename) const {
    BMP24_save((unsigned char*)_image, _height, _width, filename);
}

bool Image::ZbuffIfSet(double z, int i, int j) {
    return z_buff.ifSet(z, i, j);
}

void Image::save8bit(char* filename, char** colore) const {
    char* img = new char[_width * _height];
    for (int i = 0; i < _width; ++i)
        for (int j = 0; j < _height; ++j)
            img[_width * i + j] = (char)((_image[(_width * i + j) * 3 + 2] + _image[(_width * i + j) * 3 + 1] + _image[(_width * i + j) * 3]) / 3);

    BMP8_save(img, _height, _width, filename, colore, 256);
    delete[] img;
}

void Image::save1bit(char* filename, char** colore) const {
    unsigned char* img = new unsigned char[_width * _height];
    for (int i = 0; i < _width; ++i) {
        for (int j = 0; j < _height/8; j++) {
            unsigned char a = 0;
            for (int k = 7; k >= 0; k--)
                a += ((_image[(_width * i + j * 8 + 7 - k) * 3 + 2]) > 127 || (_image[(_width * i + j * 8 + 7 - k) * 3 + 1]) > 127 || (_image[(_width * i + j * 8 + 7 - k) * 3]) > 127) << k;
            img[_width/8 * i + j] = a;
        }
    }
    BMP1_save(img, _height, _width, filename, colore);
    delete[] img;
}

Image::~Image() {
    delete[] _image;
}

void Image::show() {
    //Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

//#pragma omp parallel for 
    for (int i = 0; i < _width; i++)
        for (int j = 0; j < _height; j++) {
            Color3 c = get(j, i);
            if (c._r > 0 || c._g > 0|| c._b > 0)
                SetPixel(mydc, j, _width - i, RGB(c._r, c._g, c._b));
        }

    ReleaseDC(myconsole, mydc);
}