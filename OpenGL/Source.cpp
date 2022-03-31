#include <iostream>
#include "Object.h"

int main() {
    int h = 1000, w = 1000;
    Color3 col(255, 255, 255);
    Image im(h, w);
    //ThreeD obj((char*)"car.obj", im);
    //ThreeD obj((char*)"StormTrooper.obj");
    ThreeD obj((char*)"deer.obj");
    obj.Norm();
    //obj.toOrdinary(900, 900, 900, 0, 0);
    obj.toTurn(0, 3.14 / 4, 0);
    obj.MoveTo(0, 0, 2);
    obj.toPerspectiv(500,500, 500, 0);
    obj.Norm();
    obj.toOrdinary(1000, 1000, 1000, 0, 0);
    obj.PreNorm();
    obj.Smooth();
    //obj.provSet(im, col);

    obj.polSet(im, col);

    //im.save((char*)"pol7.bmp");
    im.show();
}