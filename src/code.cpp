//#include <stdint.h>
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <string>
#include <cmath>
#include "colors.h"
#define CHANNEL_NUM 3

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

const vector<string> imagePaths; 
const vector<uint8_t***> images; 

//Returns all colors of the image
//crit_error - max divergence from the standart color
vector<pair<int, int>> calcColors(uint8_t*** image, int height, int width, double crit_error)
{
	vector<pair<int, int>> result;
	double min_dis = 99999999999999;
	double dis = 0;
	int index = 0;
	double red_sq;
	double green_sq;
	double blue_sq;
	result.push_back(make_pair(index, 0));
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			//Calc distance between the color of the pixel and the standart color
			for(int k = 0; k < colors.size(); k++)
			{
				red_sq = pow(image[i][j][0] - colors[k].red, 2);
				green_sq = pow(image[i][j][1] - colors[k].green, 2);
				blue_sq = pow(image[i][j][2] - colors[k].blue, 2);
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
					result.push_back(make_pair(index, 1));
				}
			} 
			min_dis = 99999999999999;
		}
	}
	return result;
}


uint8_t*** load_RGB_Image(const char* path, int& width, int& height, int& bpp)
{
	uint8_t* rgb_image = stbi_load(path, &width, &height, &bpp, 3);
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
	return image;
}

void write_RGB_PNG_Image(uint8_t*** image, int height, int width, const char* path)
{
	uint8_t* im = new uint8_t[height * width * 3];
	
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{	
			for(int k = 0; k < 3; k++)
			{
				im[i * width * 3 + j * 3 + k] = image[i][j][k];
			}
		}
	}
	
	stbi_write_png(path, width, height, CHANNEL_NUM, im, width*CHANNEL_NUM);
}

void write_RGB_JPEG_Image(uint8_t*** image, int height, int width, const char* path)
{
	uint8_t* im = new uint8_t[height * width * 3];
	
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{	
			for(int k = 0; k < 3; k++)
			{
				im[i * width * 3 + j * 3 + k] = image[i][j][k];
			}
		}
	}
	
	stbi_write_jpg(path, width, height, CHANNEL_NUM, im, width*CHANNEL_NUM);
}

bool execute(string command)
{
	if (command == "q" || command == "exit" || command != "quit")
    {
        return true;
    }
    
    if(true)
	{
		
	}
	
	return false;
}

int main(int argc, char *argv[]) 
{	
    // Display help message and quit
    if ((argc > 1) && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        cout << endl;
        
        // TODO: Add actual usage info after main functionality is implemented
        cout << "Usage: " << argv[0] << " [filenames]" << endl << endl;
        cout << "A simple program to calculate the projective cover of grass or foliage projective cover by a photo." << endl;
        return 0;
    }   
    
	string command = "";
    bool terminate = false;
    
	while(terminate != true)
	{	
		cout << "imager> ";
		cin >> command;
		terminate = execute(command);
	}
	return 0;
}
