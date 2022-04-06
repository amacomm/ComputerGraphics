#pragma once

class Color3 {
public:
    unsigned char _r, _g, _b;
    Color3(unsigned char r=0, unsigned char g=0, unsigned char b=0);
    ~Color3() {};
    Color3 intensity(float proc);
};

class Zbuff {
    double* z_buf;
    int width, height;
public:
    Zbuff(int height = 1, int width = 1);
    ~Zbuff();
    bool ifSet(double z, int i, int j);
};

class Image {
private:
    int _width;
    int _height;
    unsigned char* _image;
    Zbuff z_buff;
public:
    Image(char* filename);
    Image(int width, int height, Color3 color = Color3(0,0,0));
    int width() const;
    int height() const;
    bool ZbuffIfSet(double z, int i, int j);
    void set(int x, int y, const Color3& value);
    const Color3& get(int x, int y) const;
    void save(char* filename) const;
    void save32bit(char* filename) const;
    void save8bit(char* filename, char** colore) const;
    void save1bit(char* filename, char** colore = new char* [2]{ new char[] { (char)0, (char)0, (char)0, (char)255 }, new char[] { (char)255, (char)255, (char)255, (char)255 } }) const;
    void show();
    ~Image();
};