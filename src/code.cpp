#include <iostream>
#include <string>
#include <cmath>

#include "image.cpp"

using namespace std;

const vector<string> imagePaths; 
const vector<uint8_t***> images; 

//Returns all colors of the image
//crit_error - max divergence from the standart color

void show_help_message(char* program_name){
    cout << endl;
        
    // TODO: Add actual usage info after main functionality is implemented
    cout << "Usage: " << program_name << " [filenames]" << endl << endl;
    cout << "A simple program to calculate the projective cover of grass or foliage projective cover by a photo." << endl;    
}

bool execute(string command)
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
                    cout << canvas[i][j][k] << endl;
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
