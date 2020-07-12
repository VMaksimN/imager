#pragma once

#include <vector>
#include "colors.h"


class Shape{

protected:
	//Coordinates of the center of the circle OR
	//Coordinates of the top left vertex of the rectangle
	int x0;
	int y0;
};


class Circle : Shape{

private:
	int radius;	
	
public:
	Circle(int x0, int y0, int radius){this->x0 = x0;
					   this->y0 = y0;
					   this->radius = radius;};
};


class Rectangle : Shape{

private:
	//Coordinates of the down right vertex of the rectangle
	int x;
	int y;
	
public:
	Rectangle(int x0, int y0, int x, int y){this->x0 = x0;
					        this->y0 = y0;
					        this->x = x;
					        this->y = y;};
};

class Image{

private:
    uint8_t*** canvas;
    int width;
    int height;
    int bpp;
    Shape selected_area;
public:
    Image();
    Image(const char* path);
    Image(uint8_t*** image);
    
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
