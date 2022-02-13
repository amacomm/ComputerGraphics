#pragma once

class Color3 {
public:
    int _r, _g, _b;
    Color3(int r, int g, int b);
    ~Color3() {};
    void intensity(double proc);
};

class Image {
private:
    int _width;
    int _height;
    unsigned char* _image;

public:
    Image(int width, int height);
    int width() const;
    int height() const;

    void set(int x, int y, const Color3& value);
    const Color3& get(int x, int y) const;

    void save(char* filename) const;

    void save8bit(char* filename, char** colore) const;

    void save1bit(char* filename, char** colore) const;

    void line(int x0, int y0, int x1, int y1, Color3 color);

    void show();

    ~Image();
};