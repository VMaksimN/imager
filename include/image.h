#pragma once

#include <vector>

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
    std::vector<std::pair<int, int>> calcColors(double crit_error);
};
