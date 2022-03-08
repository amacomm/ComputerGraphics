#include <iostream>
#include "Object.h"

int main() {
    int h = 1200, w = 1200;
    Color3 col(255, 255, 255);
    Image im(h, w);
    ThreeD obj((char*)"car.obj", im);
    //ThreeD obj((char*)"StormTrooper.obj");
    //ThreeD obj((char*)"deer.obj");
    obj.provSet(im, col, 20, 500., 500., -3.14/4, 0 , 3.14/8);
    //obj.polSet(im, col, 20, 500,500, 3.14 / 2);
    //im.save((char*)"pol7.bmp");
    im.show();
}