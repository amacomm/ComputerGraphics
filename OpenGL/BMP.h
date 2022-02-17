#pragma once
#include <iostream>
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

unsigned char* BMP1_Header(int height, int stride);
unsigned char* BMP1_info(int height, int width); 
unsigned char* BMP8_Header(int height, int stride, int colore_size);
unsigned char* BMP8_info(int height, int width, int colore_size);
unsigned char* BMP24_Header(int height, int stride);
unsigned char* BMP24_info(int height, int width);


void BMP1_save(unsigned char* image, int height, int width, char* imageFileName, char** colore, int colore_size = 2);

void BMP8_save(char* image, int height, int width, char* imageFileName, char** colore , int colore_size = 256);

void BMP24_save(unsigned char* image, int height, int width, char* imageFileName);

/*void gif(char* image, int height, int width, char* imageFileName, char** colore, int colore_size) {
    static unsigned char fileHeader[] = {
        0,0,0,0,0,0,/// signature
        0,0,        /// ширина
        0,0,        /// высота
        0,          /// всякая фигня
        0,          /// фон
        0,0         /// 0
    };

    fileHeader[0] = (unsigned char)('G');
    fileHeader[1] = (unsigned char)('I');
    fileHeader[2] = (unsigned char)('F');
    fileHeader[3] = (unsigned char)('8');
    fileHeader[4] = (unsigned char)('9');
    fileHeader[5] = (unsigned char)('a');
    fileHeader[6] = (unsigned char)(width);
    fileHeader[7] = (unsigned char)(width >> 8);
    fileHeader[8] = (unsigned char)(height);
    fileHeader[9] = (unsigned char)(height >> 8);
    fileHeader[10] = (unsigned char)(128+7+32);

    FILE* imageFile = fopen(imageFileName, "wb");

    fwrite(fileHeader, 1, 14, imageFile);

    for (int i = 0; i < colore_size; i++)
        fwrite(colore[i], 1, sizeof(char)*3, imageFile);

    static unsigned char Grafic[] = {
    0,          /// signature
    0,          /// size
    0,          /// обработка изображения
    0,          /// всякая фигня
    0, 0,       /// время смены кадров
    0,          /// индекс прозрачности
    0           /// 0
    };

    Grafic[0] = (unsigned char)(21);
    Grafic[1] = (unsigned char)(249);
    Grafic[2] = (unsigned char)(4);
    Grafic[3] = (unsigned char)(4);
    Grafic[4] = (unsigned char)(50);
    Grafic[5] = (unsigned char)(50 >> 8);//0,5 сек

    fwrite(Grafic, 1, 8, imageFile);

    static unsigned char imageHeader[] = {
    0,/// signature
    0,0,        /// строка
    0,0,        /// столбец
    0,0,        /// ширина
    0,0,        /// высота
    0,          /// всякая фигня
    0,          /// размер кода
    0          /// кол-во пикселей
    };

    imageHeader[0] = (unsigned char)(44);
    imageHeader[5] = (unsigned char)(width);
    imageHeader[6] = (unsigned char)(width >> 8);
    imageHeader[7] = (unsigned char)(height);
    imageHeader[8] = (unsigned char)(height >> 8);
    imageHeader[10] = (unsigned char)(8);


    unsigned char* infoHeader = BMP1_info(height, width);
    fwrite(Grafic, 1, 8, imageFile);

    fwrite(colore[0], 1, sizeof(char) * 4, imageFile);
    fwrite(colore[1], 1, sizeof(char) * 4, imageFile);

    for (int i = 0; i < height * width / 8; i++)
        fwrite(&image[i], 1, sizeof(char), imageFile);

    fclose(imageFile);
}
*/