#include <iostream>
#include <string>
#include <cmath>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define CHANNEL_NUM 3

#include "image.h"



////////////IMAGE///////////////////////
/////////////////////////////////////////
Image::Image(const char* path){
    load_RGB_Image(path);   
    this->selected_area = (Shape*)(new Rectangle(0,0, this->width, this->height));
}

Image::Image(uint8_t*** image, unsigned int height, unsigned int width, unsigned int bpp){
	this->canvas = image;
    	this->selected_area = (Shape*)(new Rectangle(0,0, this->width, this->height));
	this->height = height;
	this->width = width;
	this->bpp = bpp;
}

void Image::load_RGB_Image(const char* path)
{
	uint8_t* rgb_image = stbi_load(path, &this->width, &this->height, &this->bpp, 3);
	uint8_t*** image;
	image = new uint8_t**[height];
	
	for(int i = 0; i < height; i++)
	{
		image[i] = new uint8_t*[width];
		
		for(int j = 0; j < width; j++)
		{
			image[i][j] = new uint8_t[3];
			
			for(int k = 0; k < 3; k++)
			{
				image[i][j][k] = rgb_image[i * width * 3 + j * 3 + k];
			}
	
		}
	}
	
	this->canvas = image;
}


void Image::write_RGB_PNG_Image(const char* path)
{
	stbi_write_png(path, width, height, CHANNEL_NUM, this->get_flat_canvas(), width*CHANNEL_NUM);
}

void Image::write_RGB_JPEG_Image(const char* path)
{
	stbi_write_jpg(path, width, height, CHANNEL_NUM, this->get_flat_canvas(), width*CHANNEL_NUM);
}

std::vector<std::pair<unsigned int, unsigned int>> Image::calcColors(double crit_error)
{
	std::vector<std::pair<unsigned int, unsigned int>> result;
	double min_dis = 99999999999999;
	double dis = 0;
	int index = 0;
	double red_sq;
	double green_sq;
	double blue_sq;
	result.push_back(std::make_pair(index, 0));
	for(int i = 0; i < this->height; i++)
	{
		for(int j = 0; j < this->width; j++)
		{
			if(selected_area->is_point_inside(i,j))
			{
				//Calc distance between the color of the pixel and the standart color
				for(int k = 0; k < colors.size(); k++)
				{
					red_sq = pow(this->canvas[i][j][0] - colors[k].red, 2);
					green_sq = pow(this->canvas[i][j][1] - colors[k].green, 2);
					blue_sq = pow(this->canvas[i][j][2] - colors[k].blue, 2);
					dis = pow((red_sq + green_sq + blue_sq), 0.5);
					if(dis < min_dis)
					{
						min_dis = dis;
						index = k;
						if(dis <= crit_error || dis == 0)
						{
							break;
						}
					}
				}
				//Write the result to the vector
				for(int k = 0; k < result.size(); k++)
				{
					if(result[k].first == index)
					{
						result[k].second++;
						break;
					}
					if(k == result.size() - 1)
					{
						result.push_back(std::make_pair(index, 1));
					}
				} 
				min_dis = 99999999999999;
			}
		}
	}
	return result;
}

uint8_t* Image::get_flat_canvas()
{
    uint8_t* flat_canvas = new uint8_t[this->height * this->width * 3];
	
	for(int i = 0; i < this->height; i++)
	{
		for(int j = 0; j < this->width; j++)
		{	
			for(int k = 0; k < 3; k++)
			{
				flat_canvas[i * this->width * 3 + j * 3 + k] = this->canvas[i][j][k];
			}
		}
	}
	
	return flat_canvas;
}

unsigned int Image::calc_color(unsigned int radius, color color)
{
	//if distance between color of the current pixel and the shpere center (coordinates of the parameter #color)
	// is less than shpere radius then counter increases
	unsigned int counter = 0;
	for(int i = 0; i < this->height; i++)
	{
		for(int j = 0; j < this->width; j++)
		{
			if(selected_area->is_point_inside(i,j))
			{
				unsigned int x = this->canvas[i][j][0];
				unsigned int y = this->canvas[i][j][1];
				unsigned int z = this->canvas[i][j][2];
            
            			if (pow(x - color.red, 2) + pow(y - color.green, 2) + pow(z - color.blue, 2) < pow(radius, 2))
            			{
               	 		counter++;
               	 	}  
			}          
		}
	}
	return counter;
}

std::vector<unsigned int> Image::calc_user_colors(double max_error, std::vector<color> colors)
{
	std::vector<unsigned int> result(colors.size());
	double min_dis = 99999999999999;
	double dis = 0;
	unsigned int index = 0;
	double red_sq;
	double green_sq;
	double blue_sq;
	result.push_back(0); //the last element contain the number of 'other' colors
	for(int i = 0; i < this->height; i++)
	{
		for(int j = 0; j < this->width; j++)
		{
			if(selected_area->is_point_inside(i,j))
			{
				//Calc distance between the color of the pixel and the standart color
				for(int k = 0; k < colors.size(); k++)
				{
					red_sq = pow(this->canvas[i][j][0] - colors[k].red, 2);
					green_sq = pow(this->canvas[i][j][1] - colors[k].green, 2);
					blue_sq = pow(this->canvas[i][j][2] - colors[k].blue, 2);
					dis = pow((red_sq + green_sq + blue_sq), 0.5);
					if(dis < max_error)
					{
						if(dis < min_dis)
						{
							min_dis = dis;
							index = k;
						}
					}
					if(k == colors.size() - 1 && min_dis == 99999999999999)
					{
						//current color is an 'other' color
						index = colors.size();
					}
				}
				//Write the result to the vector
				result[index]++; 
				min_dis = 99999999999999;
			}
		}
	}
	return result;
}


unsigned int Image::get_width(){return width;}
unsigned int Image::get_height(){return height;}
unsigned int Image::get_bpp(){return bpp;}
uint8_t*** Image::get_canvas(){return this->canvas;}
////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////



////////SHAPE//////////////////////////
//////////////////////////////////////
unsigned int Shape::get_x0() {return x0;}
unsigned int Shape::get_y0() {return y0;}

void Shape::set_x0(unsigned int x0) {this->x0 = x0;}
void Shape::set_y0(unsigned int y0) {this->y0 = y0;}
bool Shape::is_point_inside(unsigned int x, unsigned int y){return false;}
////////////////////////////////////
////////////////////////////////////


//////CIRCLE///////////////////////////
///////////////////////////////////////
Circle::Circle(unsigned int x0, unsigned int y0, unsigned int radius)
{	
	this->x0 = x0;
	this->y0 = y0;
	this->radius = radius;
}
					 
unsigned int Circle::get_radius() {return radius;}
void Circle::set_radius(unsigned int radius) {this->radius = radius;}

bool Circle::is_point_inside(unsigned int x, unsigned int y)
{
	return std::pow(x - this->x0, 2) + std::pow(y - this->y0, 2) <= this->radius;
}
////////////////////////////////////
////////////////////////////////////

///////RECTANGLE///////////////////
///////////////////////////////////
Rectangle::Rectangle(unsigned int x0, unsigned int y0, unsigned int x, unsigned int y)
{	
	this->x0 = x0;
	this->y0 = y0;
	this->x = x;
	this->y = y;
}
					        
unsigned int Rectangle::get_x(){return x;}
unsigned int Rectangle::get_y(){return y;}
	
void Rectangle::set_x(unsigned int x){this->x = x;}
void Rectangle::set_y(unsigned int y){this->y = y;}

bool Rectangle::is_point_inside(unsigned int x, unsigned int y)
{
	return ((x >= this->x0) || (x <= this->x)) && ((y >= this->y0) || (y <= this->y));
}
///////////////////////////////////
//////////////////////////////////












