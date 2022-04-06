#pragma once
#include "Structers.h"

__interface Lights {
public:
	virtual Coord getCoord() = 0;
	virtual float getIntensity() =0;
};

class voidLight : public Lights {
public:
	voidLight(){}
	~voidLight(){}
	Coord getCoord() override {
		return Coord();
	}
	float getIntensity()override {
		return 0;
	}
};

class DotLight {
	Coord _coord;
	float _intensity;
public:
	DotLight(Coord coord = Coord(), float intensity = 1): _coord(coord), _intensity(intensity){}
	~DotLight() {}
	Coord getCoord(){
		return _coord;
	}
	float getIntensity() {
		return _intensity;
	}
};