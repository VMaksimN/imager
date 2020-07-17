#pragma once

#include <vector>
#include <QImage>
#include "colors.h"


class Shape{

protected:
	//Coordinates of the center of the circle OR
	//Coordinates of the top left vertex of the rectangle
	unsigned int x0;
	unsigned int y0;

public:
	unsigned int get_x0();
	unsigned int get_y0();
	
	void set_x0(unsigned int x0);
	void set_y0(unsigned int y0);
	
	virtual bool is_point_inside(unsigned int x, unsigned int y);
};


class Circle : Shape{

private:
	unsigned int radius;	
	
public:
	Circle(){}
	Circle(unsigned int x0, unsigned int y0, unsigned int radius);
					 
	unsigned int get_radius();
	void set_radius(unsigned int radius);
	
	bool is_point_inside(unsigned int x, unsigned int y) override;
};


class Rectangle : Shape{

private:
	//Coordinates of the down right vertex of the rectangle
	unsigned int x;
	unsigned int y;
	
public:
	Rectangle(){}
	Rectangle(unsigned int x0, unsigned int y0, unsigned int x, unsigned int y);
					        
	unsigned int get_x();
	unsigned int get_y();
	
	void set_x(unsigned int x);
	void set_y(unsigned int y);
	
	bool is_point_inside(unsigned int x, unsigned int y) override;
};

extern const Rectangle* full_selection;

struct Image_info{
    QImage image;
    std::vector<std::pair<QColor, int>> colors;
};

class ImageCalculator {

public:
    static std::vector<unsigned int> calc_user_colors(QImage image, double max_error, std::vector<QColor> colors);
    static unsigned int calc_color(QImage image, unsigned int radius, QColor color);
    static int CalcGreen(QImage image, double max_error, int rangeX, int rangeY);
    static Image_info kmeans_calc(QImage image);
};
