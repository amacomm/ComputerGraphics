#include <iostream>
#include "Object.h"

int main() {
    int h = 1000, w = 1000;
    Color3 col(255, 255, 255);
    Image im(h, w);
    //ThreeD obj((char*)"car.obj", im);
    //ThreeD obj((char*)"StormTrooper.obj");
    ThreeD obj((char*)"deer.obj");
    //obj.provSet(im, col, 20, 500., 500., -3.14/4, 0 , 3.14/8);
    obj.toTurn(0, -3.13 / 4, 0);
    obj.polSet(im, col);
    obj.toDisplayCord(10000, 10000, 500, 0, 0, 0, 25000);

    //im.save((char*)"pol7.bmp");
    im.show();
}