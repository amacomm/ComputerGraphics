#include <iostream>
#include "Object.h"
#include "BMP.h"
#include <string>

int main() {
    int h = 1000, w = 1000;
    Color3 col(255, 255, 255);
    //Image text1((char*)"png.bmp");

    Image im(h, w);
    //ThreeD obj((char*)"car.obj");
    ThreeD obj((char*)"StormTrooper.obj");
    //ThreeD obj((char*)"cube.obj");
    //ThreeD obj((char*)"deer.obj");
    //ThreeD obj((char*)"Globe.obj");
    obj.ToCenter();
    obj.Norm();
    //obj.toOrdinary(900, 900, 900, 0, 0);
    obj.toTurn(0, 3*3.14f/4 , 0);
    //obj.MoveTo(0, 0, 1);
    //obj.toPerspectiv(300,300, 500, 500);
    //obj.toTurn(0, 3.14f/2.1, 0);

    //obj.Norm();
    obj.toOrdinary(300, 300, 300, 500, 500);
    obj.PreNorm();
    obj.Smooth();
    //obj.provSet(im, col);
    //obj.toOrdinary(0.66, 0.66, 0.66, 175, 175,140);
    //for (int i = 0; i < 60; i++)
    //{
    //    obj.ClearLight();
    //    obj.AddLight(DotLight(Coord(sin(-3 * 3.1416 / 2 - 0.07854 * i), 0, cos(3*3.1416/2- 0.07854 *i)), 1));
    //    obj.polSet(im, col);
    //
    //    im.save((char*)(const_cast<char*>((std::to_string(i)+ ".bmp").c_str())));
    //}
    //obj.ClearLight();
    obj.AddLight(DotLight(Coord(0, 0, 1), 1));
    ////obj.AddLight(DotLight(Coord(1, 0, 0), 1));
    ////Image text((char*)"texturesLow.bmp");
    ////obj.polSet(im, text);
    obj.polSet(im, col);
    //
    im.save((char*)"tp.bmp");
    //im.show();
}