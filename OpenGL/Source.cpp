#include <iostream>
#include "Object.h"
#include "BMP.h"
#include <string>
#include "Polar.h"
#include "Music.h"

//int main() {
//    int h = 1000, w = 1000;
//    Color3 col(255, 255, 255);
//    //Image text1((char*)"png.bmp");
//
//    Image im(h, w);
//    //ThreeD obj((char*)"car.obj");
//    ThreeD obj((char*)"StormTrooper.obj");
//    //ThreeD obj((char*)"cube.obj");
//    //ThreeD obj((char*)"deer.obj");
//    //ThreeD obj((char*)"Globe.obj");
//    obj.ToCenter();
//    obj.Norm();
//    //obj.toOrdinary(900, 900, 900, 0, 0);
//    obj.toTurn(0, 3*3.14f/4 , 0);
//    //obj.MoveTo(0, 0, 1);
//    //obj.toPerspectiv(300,300, 500, 500);
//    //obj.toTurn(0, 3.14f/2.1, 0);
//
//    //obj.Norm();
//    obj.toOrdinary(300, 300, 300, 500, 500);
//    obj.PreNorm();
//    obj.Smooth();
//    //obj.provSet(im, col);
//    //obj.toOrdinary(0.66, 0.66, 0.66, 175, 175,140);
//    //for (int i = 0; i < 60; i++)
//    //{
//    //    obj.ClearLight();
//    //    obj.AddLight(DotLight(Coord(sin(-3 * 3.1416 / 2 - 0.07854 * i), 0, cos(3*3.1416/2- 0.07854 *i)), 1));
//    //    obj.polSet(im, col);
//    //
//    //    im.save((char*)(const_cast<char*>((std::to_string(i)+ ".bmp").c_str())));
//    //}
//    //obj.ClearLight();
//    obj.AddLight(DotLight(Coord(0, 0, 1), 1));
//    ////obj.AddLight(DotLight(Coord(1, 0, 0), 1));
//    ////Image text((char*)"texturesLow.bmp");
//    ////obj.polSet(im, text);
//    obj.polSet(im, col);
//    //
//    im.save((char*)"tp.bmp");
//    //im.show();
//}

void Sempl1(Music& mus) {
    mus.AddNote(0.25, 1, Note::C, Octave::Small);
    mus.AddNote(0.25, 1, Note::D, Octave::Small);
    mus.AddNote(0.25, 1, Note::E, Octave::Small);
    mus.AddNote(0.25, 1, Note::G, Octave::Small);
    mus.AddNote(0.25, 1, Note::C, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::D, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::E, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::G, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::C, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::D, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::E, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::G, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::C, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::D, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::E, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::G, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::C, Octave::ForthLine);
    mus.AddNote(0.25, 1, Note::G, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::E, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::D, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::C, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::G, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::E, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::D, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::C, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::G, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::E, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::D, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::C, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::G, Octave::Small);
    mus.AddNote(0.25, 1, Note::E, Octave::Small);
    mus.AddNote(0.25, 1, Note::D, Octave::Small);
}
void Sempl1n(Music& mus, double s=0) {
    mus.AddTo(s+0,0.25, 1,      Note::C, (Octave)(Octave::Small-1));
    mus.AddTo(s+0.25,0.25, 1,   Note::D,   (Octave)(Octave::Small-1));
    mus.AddTo(s+0.25*2,0.25, 1, Note::E, (Octave)(Octave::Small-1));
    mus.AddTo(s+0.25*3,0.25, 1, Note::G, (Octave)(Octave::Small-1));
    mus.AddTo(s+0.25*4,0.25, 1, Note::C, (Octave)(Octave::FirstLine-1));
    mus.AddTo(s+0.25*5,0.25, 1, Note::D, (Octave)(Octave::FirstLine-1));
    mus.AddTo(s+0.25*6,0.25, 1, Note::E, (Octave)(Octave::FirstLine-1));
    mus.AddTo(s+0.25*7,0.25, 1, Note::G, (Octave)(Octave::FirstLine-1));
    mus.AddTo(s+0.25*8,0.25, 1, Note::C, (Octave)(Octave::SecondLine -1));
    mus.AddTo(s+0.25*9,0.25, 1, Note::D, (Octave)(Octave::SecondLine -1));
    mus.AddTo(s+0.25*10,0.25, 1, Note::E,(Octave)( Octave::SecondLine-1));
    mus.AddTo(s+0.25*11,0.25, 1, Note::G,(Octave)( Octave::SecondLine-1));
    mus.AddTo(s+0.25*12,0.25, 1, Note::C,(Octave)( Octave::TherdLine-1));
    mus.AddTo(s+0.25*13,0.25, 1, Note::D,(Octave)( Octave::TherdLine-1));
    mus.AddTo(s+0.25*14,0.25, 1, Note::E,(Octave)( Octave::TherdLine-1));
    mus.AddTo(s+0.25*15,0.25, 1, Note::G,(Octave)( Octave::TherdLine-1));
    mus.AddTo(s+0.25*16,0.25, 1, Note::C,(Octave)( Octave::ForthLine-1));
    mus.AddTo(s+0.25*17,0.25, 1, Note::G,(Octave)( Octave::TherdLine-1));
    mus.AddTo(s+0.25*18,0.25, 1, Note::E,(Octave)( Octave::TherdLine-1));
    mus.AddTo(s+0.25*19,0.25, 1, Note::D,(Octave)( Octave::TherdLine-1));
    mus.AddTo(s+0.25*20,0.25, 1, Note::C,(Octave)( Octave::TherdLine-1));
    mus.AddTo(s+0.25*21,0.25, 1, Note::G,(Octave)( Octave::SecondLine-1));
    mus.AddTo(s+0.25*22,0.25, 1, Note::E,(Octave)( Octave::SecondLine-1));
    mus.AddTo(s+0.25*23,0.25, 1, Note::D,(Octave)( Octave::SecondLine-1));
    mus.AddTo(s+0.25*24,0.25, 1, Note::C,(Octave)( Octave::SecondLine-1));
    mus.AddTo(s+0.25*25,0.25, 1, Note::G,(Octave)( Octave::FirstLine-1));
    mus.AddTo(s+0.25*26,0.25, 1, Note::E,(Octave)( Octave::FirstLine-1));
    mus.AddTo(s+0.25*27,0.25, 1, Note::D,(Octave)( Octave::FirstLine-1));
    mus.AddTo(s+0.25*28,0.25, 1, Note::C,(Octave)( Octave::FirstLine-1));
    mus.AddTo(s+0.25*29,0.25, 1, Note::G,(Octave)( Octave::Small-1));
    mus.AddTo(s+0.25*30,0.25, 1, Note::E,(Octave)( Octave::Small-1));
    mus.AddTo(s+0.25*31,0.25, 1, Note::D,(Octave)( Octave::Small-1));
}

void Sempl2(Music& mus) {
    mus.AddNote(0.25, 1, Note::A, Octave::Great);
    mus.AddNote(0.25, 1, Note::B, Octave::Great);
    mus.AddNote(0.25, 1, Note::C, Octave::Small);
    mus.AddNote(0.25, 1, Note::E, Octave::Small);
    mus.AddNote(0.25, 1, Note::A, Octave::Small);
    mus.AddNote(0.25, 1, Note::B, Octave::Small);
    mus.AddNote(0.25, 1, Note::C, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::E, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::A, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::B, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::C, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::E, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::A, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::B, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::C, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::E, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::A, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::E, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::C, Octave::TherdLine);
    mus.AddNote(0.25, 1, Note::B, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::A, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::E, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::C, Octave::SecondLine);
    mus.AddNote(0.25, 1, Note::B, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::A, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::E, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::C, Octave::FirstLine);
    mus.AddNote(0.25, 1, Note::B, Octave::Small);
    mus.AddNote(0.25, 1, Note::A, Octave::Small);
    mus.AddNote(0.25, 1, Note::E, Octave::Small);
    mus.AddNote(0.25, 1, Note::D, Octave::Small);
    mus.AddNote(0.25, 1, Note::B, Octave::Great);
}                              
void Sempl2n(Music& mus, double s=0) {
    mus.AddTo(s + 0, 0.25, 1, Note::A, (Octave)(Octave::Great - 1));
    mus.AddTo(s + 0.25, 0.25, 1, Note::B, (Octave)(Octave::Great - 1));
    mus.AddTo(s + 0.25 * 2, 0.25, 1, Note::C, (Octave)(Octave::Small - 1));
    mus.AddTo(s + 0.25 * 3, 0.25, 1, Note::E, (Octave)(Octave::Small - 1));
    mus.AddTo(s + 0.25 * 4, 0.25, 1, Note::A, (Octave)(Octave::Small - 1));
    mus.AddTo(s + 0.25 * 5, 0.25, 1, Note::B, (Octave)(Octave::Small - 1));
    mus.AddTo(s + 0.25 * 6, 0.25, 1, Note::C, (Octave)(Octave::FirstLine - 1));
    mus.AddTo(s + 0.25 * 7, 0.25, 1, Note::E, (Octave)(Octave::FirstLine - 1));
    mus.AddTo(s + 0.25 * 8, 0.25, 1, Note::A, (Octave)(Octave::FirstLine - 1));
    mus.AddTo(s + 0.25 * 9, 0.25, 1, Note::B, (Octave)(Octave::FirstLine - 1));
    mus.AddTo(s + 0.25 * 10, 0.25, 1, Note::C, (Octave)(Octave::SecondLine - 1));
    mus.AddTo(s + 0.25 * 11, 0.25, 1, Note::E, (Octave)(Octave::SecondLine - 1));
    mus.AddTo(s + 0.25 * 12, 0.25, 1, Note::A, (Octave)(Octave::SecondLine - 1));
    mus.AddTo(s + 0.25 * 13, 0.25, 1, Note::B, (Octave)(Octave::SecondLine - 1));
    mus.AddTo(s + 0.25 * 14, 0.25, 1, Note::C, (Octave)(Octave::TherdLine - 1));
    mus.AddTo(s + 0.25 * 15, 0.25, 1, Note::E, (Octave)(Octave::TherdLine - 1));
    mus.AddTo(s + 0.25 * 16, 0.25, 1, Note::A, (Octave)(Octave::TherdLine - 1));
    mus.AddTo(s + 0.25 * 17, 0.25, 1, Note::E, (Octave)(Octave::TherdLine - 1));
    mus.AddTo(s + 0.25 * 18, 0.25, 1, Note::C, (Octave)(Octave::TherdLine - 1));
    mus.AddTo(s + 0.25 * 19, 0.25, 1, Note::B, (Octave)(Octave::SecondLine - 1));
    mus.AddTo(s + 0.25 * 20, 0.25, 1, Note::A, (Octave)(Octave::SecondLine - 1));
    mus.AddTo(s + 0.25 * 21, 0.25, 1, Note::E, (Octave)(Octave::SecondLine - 1));
    mus.AddTo(s + 0.25 * 22, 0.25, 1, Note::C, (Octave)(Octave::SecondLine - 1));
    mus.AddTo(s + 0.25 * 23, 0.25, 1, Note::B, (Octave)(Octave::FirstLine - 1));
    mus.AddTo(s + 0.25 * 24, 0.25, 1, Note::A, (Octave)(Octave::FirstLine - 1));
    mus.AddTo(s + 0.25 * 25, 0.25, 1, Note::E, (Octave)(Octave::FirstLine - 1));
    mus.AddTo(s + 0.25 * 26, 0.25, 1, Note::C, (Octave)(Octave::FirstLine - 1));
    mus.AddTo(s + 0.25 * 27, 0.25, 1, Note::B, (Octave)(Octave::Small - 1));
    mus.AddTo(s + 0.25 * 28, 0.25, 1, Note::A, (Octave)(Octave::Small - 1));
    mus.AddTo(s + 0.25 * 29, 0.25, 1, Note::E, (Octave)(Octave::Small - 1));
    mus.AddTo(s + 0.25 * 30, 0.25, 1, Note::D, (Octave)(Octave::Small - 1));
    mus.AddTo(s + 0.25 * 31, 0.25, 1, Note::B, (Octave)( Octave::Great-1));
}

int main() {
    Music mus;
    Sempl1(mus);
    Sempl2(mus);
    Sempl1(mus);
    Sempl2(mus);
    Sempl1n(mus);
    Sempl2n(mus, 31*0.25);
    Sempl1n(mus, 31*0.5);
    Sempl2n(mus, 31*0.75);
    /*for (int j = 0; j < 8; j++)
        for (int i = 0; i < 12; i++)
            mus.AddNote(0.5, 1, (Note)i, (Octave)j);
    int f = 0;
    for (int j = 7; j >= 0; j--)
        for (int i = 11; i >=0; i--)
            mus.AddTo(1 + 0.5 * f++, 0.5, 1, (Note)i, (Octave)j);*/
    mus.save((char*)"not.wav");
    /*int h = 480, w = 480;
    Color3 col(255, 255, 255);
    Image im(h, w);
    Sphere s1(15, Color3(255, 0, 0));
    Sphere s2(15, Color3(255, 165, 0));
    Sphere s3(15, Color3(255, 255, 0));
    Sphere s4(15, Color3(0, 255, 0));
    Sphere s5(15, Color3(0, 0, 255));
    Sphere s6(15, Color3(139, 0, 255));
    Polar pol;
    pol.Add(s1, 15, 0);
    pol.Add(s2, 50 , 0);
    pol.Add(s3, 110, 0);
    pol.Add(s4, 145, 0);
    pol.Add(s5, 180, 0);
    pol.Add(s6, 215, 0);
    for (int i = 0; i < 30; i++)
    {
        im.clear();
        pol.BindSort(col);
        pol.Move(0, 0, 3*0.02618);
        pol.Move(1, 0, 3*asin(sin(0.02618) * 15 / 50));
        pol.Move(2, 0, 3*asin(sin(0.02618) * 15 / 110));
        pol.Move(3, 0, 3*asin(sin(0.02618) * 15 / 145));
        pol.Move(4, 0, 3*asin(sin(0.02618) * 15 / 180));
        pol.Move(5, 0, 3*asin(sin(0.02618) * 15 / 215));
        pol.Show(im);
        pol.ClearBind();
        im.save((char*)(const_cast<char*>(("krujochki\\" + std::to_string(i) + ".bmp").c_str())));
    }*/
    //pol.BindSort(col);
    //pol.Move(0, 0, 240*0.02618);
    //pol.Move(1, 0, 240*asin(sin(0.02618) * 25 / 80));
    //pol.Move(2, 0, 240*asin(sin(0.02618) * 25 / 135));
    //pol.Move(3, 0, 240*asin(sin(0.02618) * 25 / 190));
    //pol.Move(4, 0, 240*asin(sin(0.02618) * 25 / 245));
    //pol.Move(5, 0, 240*asin(sin(0.02618) * 25 / 300));
    //pol.Show(im);
    //pol.ClearBind();
    //im.save((char*)"tp.bmp");
    //im.show();
}