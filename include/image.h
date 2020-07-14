#pragma once

#include <vector>
#include "colors.h"


class Shape{

protected:
	//Coordinates of the center of the circle OR
	//Coordinates of the top left vertex of the rectangle
	unsigned int x0;
	unsigned int y0;

public:
	unsigned int get_x0();
	unsigned int get_y0();
	
	void set_x0(unsigned int x0);
	void set_y0(unsigned int y0);
	
	virtual bool is_point_inside(unsigned int x, unsigned int y);
};


class Circle : Shape{

private:
	unsigned int radius;	
	
public:
	Circle(){}
	Circle(unsigned int x0, unsigned int y0, unsigned int radius);
					 
	unsigned int get_radius();
	void set_radius(unsigned int radius);
	
	bool is_point_inside(unsigned int x, unsigned int y) override;
};


class Rectangle : Shape{

private:
	//Coordinates of the down right vertex of the rectangle
	unsigned int x;
	unsigned int y;
	
public:
	Rectangle(){}
	Rectangle(unsigned int x0, unsigned int y0, unsigned int x, unsigned int y);
					        
	unsigned int get_x();
	unsigned int get_y();
	
	void set_x(unsigned int x);
	void set_y(unsigned int y);
	
	bool is_point_inside(unsigned int x, unsigned int y) override;
};

const Rectangle* full_selection = new Rectangle(-1,-1,-1,-1);

class Image{

private:
    uint8_t*** canvas;
    int width;
    int height;
    int bpp;
    Shape* selected_area;
public:
    Image();
    Image(const char* path);
    Image(uint8_t*** image, unsigned int height, unsigned int width, unsigned int bpp);
    
    void load_RGB_Image(const char* path);
    void write_RGB_PNG_Image(const char* path);
    void write_RGB_JPEG_Image(const char* path);
    
    std::vector<std::pair<unsigned int, unsigned int>> calcColors(double crit_error);
    unsigned int calc_color(unsigned int radius, color color);
    std::vector<unsigned int> calc_user_colors(double max_error, std::vector<color> colors);
    
    unsigned int get_width();
    unsigned int get_height();
    unsigned int get_bpp();
    uint8_t*** get_canvas();
    uint8_t* get_flat_canvas();
    void get_selected_pixels();
};
