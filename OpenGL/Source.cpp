#include <iostream>
#include "Object.h"

int main() {
    ThreeD obj((char*)"StormTrooper.obj");
    //ThreeD obj((char*)"deer.obj");
    int h = 1024, w = 1024;
    Color3 col(255, 255, 255);
    Image im(h, w);
    obj.provSet(im, col, 155, 500., 500., 3.14/8, 3.14/8,-3.14/8);
    //obj.polSet(im, col, 155, 500,500);
    //im.save((char*)"pol7.bmp");
    im.show();
}