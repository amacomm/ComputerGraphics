#pragma once
#include "Image.h"
#include <cmath>
#include "Structers.h"
#include "Emitters.h"

class ThreeD {
    int _sizeCoord;
    int _sizeNorm;
    int _sizeText;
    int _sizeTri;
    int _sizeLight;
    Coord* _coord;
    TexturaCoord* _textCoord;
    Norm* _norm;
    Triangle* _tri;
    DotLight* _lights;
public:

    ThreeD(const char* filename);
    ThreeD();
    ~ThreeD();

    void provSet(Image& image, Color3 color);
    void polSet(Image& image, Image& text);
    void polSet(Image& image, Color3 color);
    void line(Image& image, int x0, int y0, int x1, int y1, Color3 color, float z0 = 0, float z1 = 0);
    void triangle(Triangle tri, Image& image, Image& text);
    void toPerspectiv(float ax, float ay, int u0=0, int v0=0);
    void toOrdinary(float ax, float ay, float az, int u0=0, int v0=0, float z0 = 0);
    void MoveTo(float x = 0, float y = 0, float z = 0);
    void MoveTo(Coord coord);
    void toTurn(float a, float b, float c);
    void Norm();
    void PreNorm();
    void Smooth();
    void ToCenter();
    void AddLight(DotLight light) {
        DotLight* newLight = new DotLight[++_sizeLight];
        newLight[_sizeLight - 1] = light;
        for (int i = 0; i < _sizeLight-1; i++)
        {
            newLight[i] = _lights[i];
        }
        if (_lights)
            delete[] _lights;
        _lights = newLight;
    }
    void ClearLight() {
        _sizeLight = 0;
    }
    void SwitchNorm() {
        for (int i = 0; i < _sizeTri; i++)
        {
            _tri[i]._norm1 = -_tri[i]._norm1;
            _tri[i]._norm2 = -_tri[i]._norm2;
            _tri[i]._norm3 = -_tri[i]._norm3;

        }
    }
};