//#include <stdint.h>
#include <iostream>
//#include <cmath>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <string>
#include <cmath>
#define CHANNEL_NUM 3

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;


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

void color_Decrease(uint8_t*** image, double red_coeff, double green_coeff, double blue_coeff, int height, int width)
{
	if(red_coeff == 0)
	{
		red_coeff = 1;
	}
		
	if(green_coeff == 0)
	{
		green_coeff = 1;
	}
		
	if(blue_coeff == 0)
	{
		blue_coeff = 1;
	}	
	
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			image[i][j][0] = round((double)image[i][j][0] / red_coeff) * red_coeff;
			image[i][j][1] = round((double)image[i][j][1] / green_coeff) * green_coeff;
			image[i][j][2] = round((double)image[i][j][2] / blue_coeff) * blue_coeff;
		}
	}
}

void pixelize(uint8_t*** image, double coeff, int height, int width)
{
	uint16_t sum_red = 0;
	uint16_t sum_green = 0;
	uint16_t sum_blue = 0;
	
	uint8_t aver_red = 0;
	uint8_t aver_green = 0;
	uint8_t aver_blue = 0;
	
	int h_lim = 0;
	int w_lim = 0;
	
	for(int i = 0; i < height; i+=coeff)
	{
		for(int j = 0; j < width; j+=coeff)
		{
			h_lim = i + coeff;
			if(h_lim > height)
			{
				h_lim = height;
			}
			
			w_lim = j + coeff;
			if(w_lim > width)
			{
				w_lim = width;
			}
			for(int k = i; k < h_lim; k++)
			{
				for(int l = j; l < w_lim; l++)
				{
					sum_red += image[k][l][0];
					sum_green += image[k][l][1];
					sum_blue += image[k][l][2];
				}
			}
			aver_red = sum_red / (coeff * coeff);
			aver_green = sum_green / (coeff * coeff);
			aver_blue = sum_blue / (coeff * coeff);
			
			for(int k = i; k < h_lim; k++)
			{
				for(int l = j; l < w_lim; l++)
				{
					image[k][l][0] = aver_red;
					image[k][l][1] = aver_green;
					image[k][l][2] = aver_blue;
				}
			}
			
			sum_red = 0;
			sum_green = 0;
			sum_blue = 0;
		}
	}
}

char* get_Path(string path)
{
	char* char_path;
	char_path = new char[path.length()];
	
	for(int i = 0; i < path.length(); i++)
	{
		char_path[i] = path[i];
	}
	
	return char_path;
}


int calc_error(int** error)
{
	return 0;
}

void make_mosaic(uint8_t*** mosaic, int height, int width, uint8_t**** particles, int** particles_sizes, int particles_num, int mosaic_coeff)
{
	
}


int calc_green(uint8_t*** image, int R, int height, int width)
{
    int counter = 0;
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
        {
            int x = image[i][j][0];
            int y = image[i][j][1];
            int z = image[i][j][2];
            
            //cout << x << " " << y << " " << z << endl;
                        
            if (pow(x, 2) + pow(y-255, 2) + pow(z, 2) < pow(R, 2))
                counter++;            
		}
	}
	return counter;
}


int main(int argc, char *argv[]) 
{
    // Initialize vars
    
    int width = 0; 
    int height = 0; 
    int bpp = 0;
    int R = 0;
    int save = 0;
    string command; 
    string path;
    
    // Starting in quiet mode if command line args are supplied
    if (argc > 1){
        
        // Display help message and quit
        if (argv[1] == "--help\n" || argv[1] == "-h\n")
        {
            cout << "Usage: " << argv[0] << "[filenames]" << endl;
            return 0;
        }
        
        for (int i = 1; i < argc; i++)
        {
            path = argv[i];
            uint8_t*** image = load_RGB_Image(get_Path(path), width, height, bpp);
            
            // Setting critical radius by default
            R = 255;
            
            cout << "For image " << argv[i] <<" green is\t" << (double)((double)calc_green(image, R, height, width) / (double)(width * height)) * 100 << "%\n";
        }
        return 0;
    }
    
    // Starting in interactive mode if no command line arguments supplied
    
    cout << "Enter full image name with extension:\t";
    cin >> path;
    uint8_t*** image = load_RGB_Image(get_Path(path), width, height, bpp);
    
    cout << "Image " << path << " loaded" << endl;
    cout << "Height: " << height << endl;
    cout << "Width: " << width << endl;
	
    cout << "Enter critical radius:\t";
	cin >> R;
    
	cout << "Green\t" << (double)((double)calc_green(image, R, height, width) / (double)(width * height)) * 100 << "%\n";
	cout << "Press enter to finish...";
	cin;
	
    return 0;
}
