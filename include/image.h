#pragma once

#include <vector>
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
    
    std::vector<std::pair<int, int>> calcColors(double crit_error);
    int calc_color(int radius, color color);
    std::vector<int> calc_user_colors(double max_error, std::vector<color> colors);
    
    int get_width(){return width;}
    int get_height(){return height;}
    int get_bpp(){return bpp;}
    uint8_t*** get_canvas(){return this->canvas;}
    uint8_t* get_flat_canvas();
};
