#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <string>
#include <cmath>
#include "colors.h"
#define CHANNEL_NUM 3

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
};

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
	uint8_t* im = new uint8_t[this->height * this->width * 3];
	
	for(int i = 0; i < this->height; i++)
	{
		for(int j = 0; j < this->width; j++)
		{	
			for(int k = 0; k < 3; k++)
			{
				im[i * this->width * 3 + j * 3 + k] = this->canvas[i][j][k];
			}
		}
	}
	
	stbi_write_png(path, width, height, CHANNEL_NUM, im, width*CHANNEL_NUM);
}

void Image::write_RGB_JPEG_Image(const char* path)
{
	uint8_t* im = new uint8_t[this->height * this->width * 3];
	
	for(int i = 0; i < this->height; i++)
	{
		for(int j = 0; j < this->width; j++)
		{	
			for(int k = 0; k < 3; k++)
			{
				im[i * this->width * 3 + j * 3 + k] = this->canvas[i][j][k];
			}
		}
	}
	
	stbi_write_jpg(path, width, height, CHANNEL_NUM, im, width*CHANNEL_NUM);
}
