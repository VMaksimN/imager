#include <iostream>
#include <string>
#include <cmath>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define CHANNEL_NUM 3

#include "image.h"

Image::Image(const char* path){
    load_RGB_Image(path);    
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

std::vector<std::pair<int, int>> Image::calcColors(double crit_error)
{
	std::vector<std::pair<int, int>> result;
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

int Image::calc_color(int radius, color color)
{
	//if distance between color of the current pixel and the shpere center (coordinates of the parameter #color)
	// is less than shpere radius then counter increases
	int counter = 0;
	for(int i = 0; i < this->height; i++)
	{
		for(int j = 0; j < this->width; j++)
		{
			int x = this->canvas[i][j][0];
			int y = this->canvas[i][j][1];
			int z = this->canvas[i][j][2];
            
            		if (pow(x - color.red, 2) + pow(y - color.green, 2) + pow(z - color.blue, 2) < pow(radius, 2))
            		{
                		counter++;
                	}            
		}
	}
	return counter;
}

std::vector<int> Image::calc_user_colors(double max_error, std::vector<color> colors)
{
	std::vector<int> result(colors.size());
	double min_dis = 99999999999999;
	double dis = 0;
	int index = 0;
	double red_sq;
	double green_sq;
	double blue_sq;
	result.push_back(0); //the last element contain the number of 'other' colors
	for(int i = 0; i < this->height; i++)
	{
		for(int j = 0; j < this->width; j++)
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
	return result;
}
