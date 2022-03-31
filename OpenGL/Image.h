#pragma once

class Color3 {
public:
    int _r, _g, _b;
    Color3(int r, int g, int b);
    ~Color3() {};
    Color3 intensity(double proc);
};

class Zbuff {
public:

    double* z_buf;
    int width, height;
    Zbuff(int height, int width) :height(height), width(width) {
        z_buf = new double[height * width];
        for (int i = 0; i < width * height; z_buf[i++] = 200000000);
    }
    ~Zbuff() {
        delete[] z_buf;
    }
    bool ifSet(double z, int i, int j) {
        if (z <= z_buf[width * i + j]) {
            z_buf[width * i + j] = z;
            return true;
        }
        return false;
    }
};

class Image {
private:
    int _width;
    int _height;
    unsigned char* _image;

public:
    Zbuff z_buff;
    Image(int width, int height);
    int width() const;
    int height() const;

    void set(int x, int y, const Color3& value);
    const Color3& get(int x, int y) const;

    void save(char* filename) const;

    void save8bit(char* filename, char** colore) const;

    void save1bit(char* filename, char** colore = new char* [2]{ new char[] { (char)0, (char)0, (char)0, (char)255 }, new char[] { (char)255, (char)255, (char)255, (char)255 } }) const;

    void line(int x0, int y0, int x1, int y1, Color3 color);

    void show();

    ~Image();
};