#pragma once
#include "Object.h"

class World {
	ThreeD* obj;
    Coord* coord;
	int sizeObj;
public:
    void Add(ThreeD objt, Coord coordt) {
        sizeObj++;
        ThreeD* newObj = new ThreeD[sizeObj];
        Coord* newCoord = new Coord[sizeObj];
        for (int i = 0; i < sizeObj - 1; i++) {
            newObj[i] = obj[i];
            newCoord[i] = coord[i];
        }
        newObj[sizeObj - 1] = objt;
        newCoord[sizeObj - 1] = coordt;
        delete obj;
        delete coord;
        obj = newObj;
        coord = newCoord;
    }
    World() {
        sizeObj = 0;
        obj = new ThreeD();
        coord = new Coord();
    }
    ~World() {
        delete[] obj;
        delete[] coord;
    }
    void MoveTo(double x = 0, double y = 0, double z = 0) {
        for (int i = 0; i < sizeObj; ++i) {
            obj[i].MoveTo(x, y, z);
        }
    }
    void toTurn(double a, double b, double c) {
        for (int i = 0; i < sizeObj; ++i) {
            coord[i]._x = cos(c) * cos(b) * coord[i]._x + sin(c) * cos(b) * coord[i]._y + sin(b) * coord[i]._z;
            coord[i]._y = (-sin(a) * sin(b) * cos(c) - sin(c) * cos(a)) * coord[i]._x + (-sin(a) * sin(b) * sin(c) + cos(a) * cos(c)) * coord[i]._y + sin(a) * cos(b) * coord[i]._z;
            coord[i]._z = (sin(a) * sin(c) - sin(b) * cos(c) * cos(a)) * coord[i]._x + (-sin(b) * cos(a) * sin(c) - sin(a) * cos(c)) * coord[i]._y + cos(a) * cos(b) * coord[i]._z;
            obj[i].toTurn(a, b, c);
        }
    }
    void polSet(Image& image, Color3 color) {
        for (int i = 0; i < sizeObj; ++i) {
            obj[i].MoveTo(coord[i]);
            obj[i].polSet(image, color);
        }
    }
};