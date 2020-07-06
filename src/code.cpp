#include <iostream>
#include <string>
#include <cmath>

#include "image.cpp"

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
