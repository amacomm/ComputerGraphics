#include "Image.h"
#include "BMP.h"
#include <windows.h>
#include <iostream>
#include <omp.h>

Color3::Color3(int r = 0, int g = 0, int b = 0) :
    _r(r), _g(g), _b(b) {};

void Color3::intensity(double proc) {
    _r *= proc;
    _g *= proc;
    _b *= proc;
}

Image::Image(int width, int height) :
    _width(width), _height(height), _image(new unsigned char[_height * _width * 3]) {
    for (int i = 0; i < _height * _width * 3; _image[i++] = (unsigned char)0);
};

int Image::width() const { return _width; }
int Image::height() const { return _height; }

void Image::set(int y, int x, const Color3& value) {
    _image[(_width * x + y) * 3 + 2] = (unsigned char)(value._r);///red
    _image[(_width * x + y) * 3 + 1] = (unsigned char)(value._g);///green
    _image[(_width * x + y) * 3 + 0] = (unsigned char)(value._b); ///blue
}
const Color3& Image::get(int x, int y) const {
    return Color3(_image[(_width * x + y) * 3 + 2], _image[(_width * x + y) * 3 + 1], _image[(_width * x + y) * 3 + 0]);
}

void Image::save(char* filename) const {
    BMP24_save((unsigned char*)_image, _height, _width, filename);
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

void Image::line(int x0, int y0, int x1, int y1, Color3 color) {
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) { // make it left-to-right
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    float derror = std::abs(dy / float(dx));
    float error = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (!(x<0 || x>=_width || y<0 || y>=_height))
        {
            if (steep)
                set(y, x, color);
            else
                set(x, y, color);
        }
        error += derror;
        if (error > .5) {
            y += (y1 > y0 ? 1 : -1);
            error -= 1.;
        }
    }
}

void Image::show() {
    //Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

    //Choose any color
    //COLORREF COLOR;
    //Draw pixels

//#pragma omp parallel for 
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++) {
            Color3 c = get(i, j);
            if (c._r > 0) {
                SetPixel(mydc, j, _width - i, RGB(c._r, c._g, c._b));
            }
        }
    }

    ReleaseDC(myconsole, mydc);
    //std::cin.ignore();
}