#include <iostream>
#include <string>
#include <cmath>
#define CHANNEL_NUM 3

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

struct user_data{
    char* paths[1];
    int radius;
};

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
            
            if (pow(x, 2) + pow(y-255, 2) + pow(z, 2) < pow(R, 2))
                counter++;            
		}
	}
	return counter;
}

void process_images(int image_count, char** paths, int radius){
    
    int summ = 0;
       
    for (int i = 0; i < image_count; i++)
    {
        int width = 0;
        int height = 0;
        int bpp = 0;
        
        uint8_t*** image = load_RGB_Image(get_Path(paths[i]), width, height, bpp);
        
        double cover = (double)((double)calc_green(image, radius, height, width) / (double)(width * height)) * 100;
            
        summ += cover;
           
        cout << "For image " << paths[i] <<" green is\t" << cover << "%\n";
    }
        
    cout << image_count << " images prosesed." << endl;
    cout << "Average green coverage: " << summ / (image_count) << "%" << endl;    
    
}

user_data get_user_data(){
    
    user_data data;
    string path;
    
    cout << "Enter full image name with extension:\t";
    cin >> path;
    data.paths[0] = get_Path(path);
        
    cout << "Enter critical radius:\t";
	cin >> data.radius;
    
    return data;
}

int main(int argc, char *argv[]) 
{
    
    // Initialize vars
    int radius = 215;
    
    // Starting in quiet mode if command line args are supplied
    
    // Display help message and quite
    if ((argc > 1) && (argv[1] == "--help\n" || argv[1] == "-h\n")) {
        cout << "Usage: " << argv[0] << "[filenames]" << endl;
        return 0;
    }   
    
    if (argc == 1) {
        user_data data = get_user_data();
        process_images(1, data.paths, data.radius);
    }
    else {
        char* paths[argc - 1];
    
        for (int i = 1; i < argc; i++){
            paths[i-1] = argv[i];
        }
        
        process_images(argc - 1, paths, radius);
    }
    
    return 0;
}
