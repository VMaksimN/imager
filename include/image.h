#pragma once

#include <vector>
#include <QImage>
#include "colors.h"

class Image{

private:
    uint8_t*** canvas;
    int width;
    int height;
    int bpp;

public:
    Image();
    Image(const char* path);
    void load_RGB_Image(const char* path);
    void write_RGB_PNG_Image(const char* path);
    void write_RGB_JPEG_Image(const char* path);    
    uint8_t*** get_canvas(){return this->canvas;}
    uint8_t* get_flat_canvas();
    std::vector<std::pair<int, int>> calcColors(double crit_error);
    int calc_color(uint8_t*** image, int height, int width, int radius, color color);
    static unsigned int calc_color(QImage image, unsigned int radius, QColor color);
};
