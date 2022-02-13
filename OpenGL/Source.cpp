#include <iostream>
#include "Object.h"

void line1(int x0, int y0, int x1, int y1, Image& image, Color3 color) {
    for (double t = 0.0; t < 1.0; t += 0.01) {
        int x = x0 * (1. - t) + x1 * t;
        int y = y0 * (1. - t) + y1 * t;
        image.set(x, y, color);
    }
}

void line2(int x0, int y0, int x1, int y1, Image& image, Color3 color) {
    for (int x = x0; x <= x1; x++) {
        float t = (x - x0) / (float)(x1 - x0);
        int y = y0 * (1. - t) + y1 * t;
        image.set(x, y, color);
    }
}

void line3(int x0, int y0, int x1, int y1, Image& image, Color3 color) {
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
    for (int x = x0; x <= x1; x++) {
        float t = (x - x0) / (float)(x1 - x0);
        int y = y0 * (1. - t) + y1 * t;
        if (steep) {
            image.set(y, x, color);
        }
        else {
            image.set(x, y, color);
        }
    }
}

void line4(int x0, int y0, int x1, int y1, Image& image, Color3 color) {
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
        if (steep) {
            image.set(y, x, color);
        }
        else {
            image.set(x, y, color);
        }
        error += derror;
        if (error > .5) {
            y += (y1 > y0 ? 1 : -1);
            error -= 1.;
        }
    }
}

/*void triangle(double x0, double y0, double x1, double y1, double x2, double y2, int h, int w, Image& image, Color3 color) {
    double xmin = std::min(std::min(x0, x1), x2) > 0 ? std::min(std::min(x0, x1), x2) : 0;
    double ymin = std::min(std::min(y0, y1), y2) > 0 ? std::min(std::min(y0, y1), y2) : 0;
    double xmax = std::max(std::max(x0, x1), x2) < w ? std::max(std::max(x0, x1), x2) : w;
    double ymax = std::max(std::max(y0, y1), y2) < h ? std::max(std::max(y0, y1), y2) : h;
    for(int x=xmin;x<xmax;x++)
        for (int y = ymin; y < ymax; y++)
        {
            bool lambda0 = ((((x1 - x2) * (y - y2) - (y1 - y2) * (x - x2)) / ((x1 - x2) * (y0 - y2) - (y1 - y2) * (x0 - x2)))>0);
            bool lambda1 = ((((x2 - x0) * (y - y0) - (y2 - y0) * (x - x0)) / ((x2 - x0) * (y1 - y0) - (y2 - y0) * (x1 - x0)))>0);
            bool lambda2 = ((((x0 - x1) * (y - y1) - (y0 - y1) * (x - x1)) / ((x0 - x1) * (y2 - y1) - (y0 - y1) * (x2 - x1)))>0);
            if (lambda0 && lambda1 && lambda2)
                image.set(x, y, color);
        }
}
*/
int main() {
    //double x0=0.5, x1=1, x2=1.5, y0=0.5, y1=2.5, y2=0.5;
    //int x=2, y=2;
    //
    //double lambda0 = ((x1 - x2) * (y - y2) - (y1 - y2)*(x - x2)) / ((x1 - x2) * (y0 - y2) - (y1 - y2)*(x0 - x2));
    //double lambda1 = ((x2 - x0) * (y - y0) - (y2 - y0)*(x - x0)) / ((x2 - x0) * (y1 - y0) - (y2 - y0)*(x1 - x0));
    //double lambda2 = ((x0 - x1) * (y - y1) - (y0 - y1)*(x - x1)) / ((x0 - x1) * (y2 - y1) - (y0 - y1)*(x2 - x1));
    //double a = lambda0 + lambda1 + lambda2;
    //int k = 0;

    //int h = 1000, w = 1000;
    //Color3 col(255, 255, 255);
    //Image im(h, w);
    //triangle(-10,  500-150, 500, 500+150, 1500,500, h, w, im, col);
    //im.save((char*)"triangle3.bmp");

    //ThreeD obj((char*)"StormTrooper.obj");
    ThreeD obj((char*)"deer.obj");
    int h = 1000, w = 1000;
    Color3 col(255, 165, 0);
    Image im(h, w);
    //obj.provSet(im, col, 0.5, 500., 0.);
    obj.polSet(im, col, 0.5, 500,10);
    //im.save((char*)"pol6.bmp");
    im.show();
}

/*int main()
{
    //int h=200, w=200;
    //Color3 col(255, 255, 255);
    //Image im(h, w);
    //for (int i = 0; i < 13; i++)
    //    line4(100, 100, 100+95*cos(2* 3.14159265358979323846 *i/13), 100 + 95 * sin(2 * 3.14159265358979323846 * i / 13), im, col);
    //im.save((char*)"alg4.bmp");

    //ThreeD obj((char*)"StormTrooper.obj");
    //int h = 1000, w = 1000;
    //Color3 col(255, 255, 255);
    //Image im(h, w);
    //for (int i = 0; i < obj._sizeCoord; i++)
    //    im.set(250*obj._coord[i]._x+500, 250*obj._coord[i]._y+500, col);
    //im.save((char*)"obj1_3.bmp");

    ThreeD obj((char*)"StormTrooper.obj");
    int h=1024, w=1024;
    Color3 col(255, 255, 255);
    Image im(h, w);
    
    obj.provSet(im, col, 150, 500);

    char** colore = new char* [256]{ new char[] { (char)0, (char)0, (char)0, (char)255 }, new char[] { (char)255, (char)255, (char)255, (char)255 } };
    //char** colore = new char* [256];
    //for (int i = 0; i < 256; i++)
    //{
    //    colore[i] = new char[] { (char)i, (char)i, (char)i, (char)255 };
    //}
    //im.save((char*)"obj3.bmp");
    im.save1bit((char*)"obj1bit.bmp", colore);
    for (int i = 0; i < 256; delete[] colore[i++]);
    delete[] colore;
}*/