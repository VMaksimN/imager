#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

#include "image.h"

const std::vector<std::string> imagePaths; 
const std::vector<uint8_t***> images; 

//Returns all colors of the image
//crit_error - max divergence from the standart color

void show_help_message(char* program_name){
    std::cout << std::endl;
        
    // TODO: Add actual usage info after main functionality is implemented
    std::cout << "Usage: " << program_name << " [filenames]" << std::endl << std::endl;
    std::cout << "A simple program to calculate the projective cover of grass or foliage projective cover by a photo." << std::endl;
}

bool execute(std::string command)
{
	if (command == "q" || command == "exit" || command == "quit")
    {
        return true;
    }
    
    // Testing if image has loaded
    if(true)
	{
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
	
	return false;
}

int main(int argc, char *argv[]) 
{	
    // Display help message and quit
    if ((argc > 1) && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        show_help_message(argv[0]);
        return 0;
    }   
    
	std::string command = "";
    bool terminate = false;
    
	while(terminate != true)
	{	
		std::cout << "imager> ";
		std::cin >> command;
		terminate = execute(command);
	}
	return 0;
}
