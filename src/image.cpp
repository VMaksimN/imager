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
std::vector<unsigned int> ImageCalculator::calc_user_colors(QImage image, double max_error, std::vector<QColor> colors)
{
	std::vector<unsigned int> result(colors.size());
	double min_dis = 99999999999999;
	double dis = 0;
	unsigned int index = 0;
	double red_sq;
	double green_sq;
	double blue_sq;
	result.push_back(0); //the last element contain the number of 'other' colors

    for(int i = 0; i < image.height(); i++)
	{
        for(int j = 0; j < image.width(); j++)
		{
			//Calc distance between the color of the pixel and the standart color
			for(int k = 0; k < colors.size(); k++)
			{
                QColor current_color = image.pixelColor(i, j);
				red_sq = pow(current_color.red() - colors[k].red(), 2);
				green_sq = pow(current_color.green() - colors[k].green(), 2);
				blue_sq = pow(current_color.blue() - colors[k].blue(), 2);
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

unsigned int ImageCalculator::calc_color(QImage image, unsigned int radius, QColor color)
{
    unsigned int counter = 0;
    for(int i = 0; i < image.width(); i++)
    {
        for(int j = 0; j < image.height(); j++)
        {
            //if(selected_area->is_point_inside(i,j))
            if (true)
            {
                QColor current_color = image.pixelColor(i, j);
                if (pow(current_color.red() - color.red(), 2) + pow(current_color.green() - color.green(), 2) + pow(current_color.blue() - color.blue(), 2) < pow(radius, 2))
                {
                    counter++;
                }
            }
        }
    }
    return counter;
}

int ImageCalculator::CalcGreen(QImage image, double max_error, int rangeX, int rangeY)

{
    std::vector<QColor> green_colors;

    green_colors.push_back(QColor("#11ff00"));
    green_colors.push_back(QColor("#0a9800"));
    green_colors.push_back(QColor("#065e00"));
    green_colors.push_back(QColor("#044700"));
    green_colors.push_back(QColor("#45a834"));
    green_colors.push_back(QColor("#307624"));
    green_colors.push_back(QColor("#437c33"));
    green_colors.push_back(QColor("#38672a"));
    green_colors.push_back(QColor("#246700"));
    green_colors.push_back(QColor("#4bd800"));

    int counter = 0;
    int offsetX = 0;
    int offsetY = 0;

    for(int i = 0; i < image.width(); i++)
    {
        for(int j = 0; j < image.height(); j++)
        {
            for(int k = 0; k < green_colors.size(); k++)
            {
                if (std::pow(image.pixelColor(i, j).red() - green_colors[k].red(), 2) +
                    std::pow(image.pixelColor(i, j).green() - green_colors[k].green(), 2) +
                    std::pow(image.pixelColor(i, j).blue() - green_colors[k].blue(), 2) <= std::pow(max_error, 2))
                {
                    offsetX = 0;
                    offsetY = 0;
                    while(i - rangeY + offsetY < 0)
                    {
                        offsetY++;
                    }
                    while(j - rangeX + offsetX < 0)
                    {
                        offsetX++;
                    }
                    int green_counter = 0;
                    for(int l = i - rangeY + offsetY; l < i + rangeY && l < image.height(); l++)
                    {
                        for(int m = j - rangeX + offsetX; m < j + rangeX && m < image.width(); m++)
                        {
                            for(int n = 0; n < green_colors.size(); n++)
                            {
                                if(std::pow(image.pixelColor(l, m).red() - green_colors[n].red(), 2) +
                                   std::pow(image.pixelColor(l, m).green() - green_colors[n].green(), 2) +
                                   std::pow(image.pixelColor(l, m).blue() - green_colors[n].blue(), 2) <= std::pow(max_error, 2))
                                {
                                    green_counter++;
                                }
                            }
                        }
                    }
                    if(green_counter >= (rangeY + 1) * (rangeX + 1) * 0.4)
                    {
                        counter++;
                        //setPixelColor(i, j, QColor(255, 255, 255, 255));
                    }
                }
            }
        }
    }
    return counter;
}

Image_info ImageCalculator::kmeans_calc(QImage image)
{
    int num_of_colors = basic_colors.size();
    int color_counters[num_of_colors];

    for (int i = 0; i < num_of_colors; i++)
    {
        color_counters[i] = 0;
    }

    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {
            QColor current_color = image.pixelColor(i, j);
            unsigned int min_dist_sq = 2147483647;
            int closest_color_index;

            for (int k = 0; k < num_of_colors; k++)
            {
                unsigned int curr_dist_sq;
                curr_dist_sq = std::pow(current_color.red() - basic_colors[k].red(), 2) +
                              std::pow(current_color.green() - basic_colors[k].green(), 2) +
                              std::pow(current_color.blue() - basic_colors[k].blue(), 2);
                if (curr_dist_sq < min_dist_sq) {
                    min_dist_sq = curr_dist_sq;
                    closest_color_index = k;
                }
            }

            color_counters[closest_color_index] += 1;
        }
    }

    Image_info result;
    result.image = image;
    for (int i = 0; i < num_of_colors; i++)
    {
        result.colors.push_back(std::make_pair(basic_colors[i], color_counters[i]));
    }

    return result;
}


////////SHAPE//////////////////////////
//////////////////////////////////////
unsigned int Shape::get_x0() {return x0;}
unsigned int Shape::get_y0() {return y0;}

void Shape::set_x0(unsigned int x0) {this->x0 = x0;}
void Shape::set_y0(unsigned int y0) {this->y0 = y0;}
bool Shape::is_point_inside(unsigned int x, unsigned int y){return false;}

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

const Rectangle* full_selection = new Rectangle(-1,-1,-1,-1);
