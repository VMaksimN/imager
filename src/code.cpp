#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

#include "image.h"


std::vector<Image> images;

void show_help_message(char* program_name){
    std::cout << std::endl;
        
    // TODO: Add actual usage info after main functionality is implemented
    std::cout << "Usage: " << program_name << " [filenames]" << std::endl << std::endl;
    std::cout << "A simple program to calculate the projective cover of grass or foliage projective cover by a photo." << std::endl;
}

std::vector<std::string> getArguments(std::string comm)
{
	std::vector<std::string> result;
	int space_pos = comm.find(" "); 
	comm = comm.substr(space_pos + 1, comm.length() - space_pos - 1);
	for(int i = 0, j = -1; i < comm.length(); i++)
	{
		if(comm[i] == ' ')
		{
			result.push_back(comm.substr(j + 1, i - (j + 1)));
			j = i;
			continue;
		}
		if(i == comm.length() - 1)
		{
			result.push_back(comm.substr(j + 1, i - j));
			break;
		}
	}
	
	return result;
}

bool execute(std::string command)
{
	if (command == "q" || command == "exit" || command == "quit")
    {
        return true;
    }
    
    //Command pattern
    //lis /some_dir/image.png /some_dir/imag0.jpg /some_dir/image1.png
    else if(command.substr(0, 3) == "lis" || command.substr(0, 10) == "loadimages")
	{
	    std::vector<std::string> arguments = getArguments(command);
	    for(int i = 0; i < arguments.size(); i++)
	    {
	        images.push_back(std::move(Image((arguments[i]).c_str())));
	    }
	}
    else if(command == "help" || command == "h")
    {
    	show_help_message("imager");
    }
    else if(command == "saveimages" || command == "sis")
    {
    	//needs template
    }
	
    return false;
}

void TEST_calc_user_colors()
{
	Image im("/home/user/Documents/t.png");
	std::vector<color> colors
	{	
		{10, 204, 7, "Some green"},
		{0, 0, 0, "Black"},
		{170, 4, 10, "Some red"},
	};
	std::vector<int> colors_pixels = im.calc_user_colors(20, colors);
	for(int i = 0; i < colors_pixels.size() - 1; i++)
	{
		std::cout << colors[i].name << "\t" << ((double)colors_pixels[i] / (double)(1920 * 1080)) * 100 << "\n"; 
	}
	
	std::cout << "Others " << "\t" << ((double)colors_pixels[colors.size()] / (double)(1920 * 1080)) * 100 << "\n";
}

void TEST_calc_color()
{
	Image im("/home/user/Documents/t.png");
	color c
	{	
		10,
		204,
		7,
		"Some green"
	};
	int pixels = im.calc_color(100, c);
	std::cout << pixels << "\n";
	std::cout << c.name << "\t" << ((double)pixels / (double)(1920 * 1080)) * 100; 
}

void TEST_load()
{	// Testing if image has loaded
	Image image("Photos/1.jpg");
       
        uint8_t*** canvas = image.get_canvas();
       
       for(int i = 0; i < 100; i++)
       {
                       
            for(int j = 0; j < 100; j++)
            {
                                
                for(int k = 0; k < 3; k++)
                {
                    std::cout << canvas[i][j][k] << std::endl;
                }
        
            }
        }
}

int main(int argc, char *argv[]) 
{	

	TEST_calc_user_colors();
    // Display help message and quit
    if ((argc > 1) && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        show_help_message(argv[0]);
        return 0;
    }   
    
	std::string command = "";
    bool terminate = false;
    
	while (terminate != true)
	{	
		std::cout << "imager> ";
		std::cin >> command;
		terminate = execute(command);
	}
	
	return 0;
}
