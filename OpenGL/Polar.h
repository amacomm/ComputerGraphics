#pragma once
#include "Image.h"
#include <cmath>

class Sphere {
public:
	float _r;
	Color3 _color;
	Sphere(float r =1, Color3 color = Color3()): _r(r), _color(color) {
	}
	
};

class Line {
public:
	float _r1, _r2, _fi1, _fi2;
	Color3 _color;
	Line(float r1=0, float r2=0, float fi1=0, float fi2=0, Color3 color = Color3()): _r1(r1), _r2(r2), _fi1(fi1), _fi2(fi2), _color(color) {

	}
};

class Polar {
	Sphere* _sphere;
	Line* _line;
	int _sizeLine;
	int _sizeSphere;
	float* _r;
	float* _fi;
	int _h, _w;
public:
	Polar() : _sizeSphere(0), _sphere(new Sphere[1]), _h(0), _w(0), _sizeLine(0), _line(new Line[1]) {
		float* r = new float[1], * fi = new float[1];
		for (int i = 0; i < 1; r[i] = 0, fi[i++] = 0);
	}
	Polar(Sphere* sphere, int size): _sizeSphere(size), _sphere(sphere), _h(0), _w(0), _sizeLine(0),  _line(new Line[1]){
		float* r = new float[size], * fi = new float[size];
		for (int i = 0; i < size; r[i] = 0, fi[i++] = 0);
	}
	Sphere* Add(Sphere sphere, float r=0, float fi =0) {
		Sphere* newSphere = new Sphere[++_sizeSphere];
		float* newR = new float[_sizeSphere], * newFi = new float[_sizeSphere];
		newSphere[_sizeSphere - 1] = sphere;
		newR[_sizeSphere - 1] = r;
		newFi[_sizeSphere - 1] = fi;
		for (int i = 0; i < _sizeSphere - 1; i++) {
			newSphere[i] = _sphere[i];
			newR[i] = _r[i];
			newFi[i] = _fi[i];
		}
		delete[] _sphere;
		delete[] _r;
		delete[] _fi;
		_sphere = newSphere;
		_r = newR;
		_fi = newFi;
		return &newSphere[_sizeSphere - 1];
	}
	void Add(Sphere* sphere, float r = 0, float fi = 0) {
		Sphere* newSphere = new Sphere[++_sizeSphere];
		float* newR = new float[_sizeSphere], * newFi = new float[_sizeSphere];
		newSphere[_sizeSphere - 1] = *sphere;
		newR[_sizeSphere - 1] = r;
		newFi[_sizeSphere - 1] = fi;
		for (int i = 0; i < _sizeSphere - 1; i++) {
			newSphere[i] = _sphere[i];
			newR[i] = _r[i];
			newFi[i] = _fi[i];
		}
		delete[] _sphere;
		delete[] _r;
		delete[] _fi;
		_sphere = newSphere;
		_r = newR;
		_fi = newFi;
		delete sphere;
		sphere = &newSphere[_sizeSphere - 1];
	}
	void Move(int i, float r=0, float fi =0) {
		if (i<0 || i>_sizeSphere - 1) return;
		_r[i] += r;
		_fi[i] += fi;
	}
	void Move(Sphere& sphere, float r = 0, float fi = 0) {
		for (int i = 0; i < _sizeSphere; i++)
			if (&_sphere[i] == &sphere) { Move(i, r, fi); return; }
	}
	void MoveTo(int i, float r = 0, float fi = 0) {
		if (i<0 || i>_sizeSphere - 1) return;
		_r[i] = r;
		_fi[i] = fi;
	}
	void MoveTo(Sphere& sphere, float r = 0, float fi = 0) {
		for (int i = 0; i < _sizeSphere; i++)
			if (&_sphere[i] == &sphere) { MoveTo(i, r, fi); return; }
	}
	void Show(Image &image) {
		for (int i = 0; i < _sizeLine; ++i) {
			int x1, y1, x2, y2;
			x1 = image.width() / 2 + cos(_line[i]._fi1) * _line[i]._r1 + _h;
			y1 = image.height() / 2 + sin(_line[i]._fi1) * _line[i]._r1 + _w;
			x2 = image.width() / 2 + cos(_line[i]._fi2) * _line[i]._r2 + _h;
			y2 = image.height() / 2 + sin(_line[i]._fi2) * _line[i]._r2 + _w;
			line(image, x1, y1, x2, y2, _line[i]._color);
		}
		for (int i = 0; i < _sizeSphere; ++i) {
			int xmin, xmax, ymin, ymax, x, y;
			x = image.width()/2+cos(_fi[i]) * _r[i]+_h;
			y = image.height()/2+sin(_fi[i]) * _r[i]+_w;

			xmin = x-_sphere[i]._r > 0 ? x - _sphere[i]._r : 0;
			ymin = y - _sphere[i]._r > 0 ? y - _sphere[i]._r : 0;
			xmax = x + _sphere[i]._r < image.width() ? x + _sphere[i]._r : image.width();
			ymax = y + _sphere[i]._r < image.height() ? y + _sphere[i]._r : image.height();
			for (int u = (int)xmin; u < xmax; u++)
				for (int v = (int)ymin; v < ymax; v++)
				{
					if(std::sqrt((u-x)* (u - x)+ (v - y)* (v - y))<_sphere[i]._r)
						image.set(u, v, _sphere[i]._color);
				}
		}
	}
	void Bind(int i, int j, Color3 color = Color3()) {
		Line* newLine = new Line[++_sizeLine];
		newLine[_sizeLine - 1] = Line(_r[i], _r[j], _fi[i], _fi[j], color);
		for (int t = 0; t < _sizeLine-1; t++)
		{
			newLine[t] = _line[t];
		}
		delete[] _line;
		_line = newLine;
	}
	void Bind(Sphere& sphere1, Sphere& sphere2, Color3 color = Color3()) {
		int n, k;
		for (int i = 0; i < _sizeSphere; i++)
		{
			if (&sphere1 == &_sphere[i]) n = i;
			if (&sphere2 == &_sphere[i]) k = i;
		}
		Bind(n, k, color);
	}
	void BindSort(Color3 color = Color3()) {
		for (int i = 0; i < _sizeSphere-1; i++)
			Bind(i, i + 1, color);
	}
	void BindAll(Color3 color = Color3()) {
		for (int i = 0; i < _sizeSphere; ++i)
			for (int j = i+1; j < _sizeSphere; j++)
				Bind(i, j, color);
	}
	void ClearBind() {
		_sizeLine = 0;
	}
	void line(Image& image, int x0, int y0, int x1, int y1, Color3 color) {
		bool steep = false;
		if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
			std::swap(x0, y0);
			std::swap(x1, y1);
			steep = true;
		}
		if (x0 > x1) {
			std::swap(x0, x1);
			std::swap(y0, y1);
		}
		int dx = x1 - x0;
		int dy = y1 - y0;
		float derror = std::abs(dy / float(dx));
		float error = 0;
		int y = y0;
		for (int x = x0; x <= x1; x++) {
			if (!(x < 0 || x >= image.width() || y < 0 || y >= image.height()))
			{
				if (steep) image.set(y, x, color);
				else image.set(x, y, color);
			}
			error += derror;
			if (error > .5) {
				y += (y1 > y0 ? 1 : -1);
				error -= 1.;
			}
		}
	}

	~Polar() {
		delete[] _sphere;
		_sizeSphere = 0;
	}
};