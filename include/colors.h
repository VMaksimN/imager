#pragma once

#include <string>
#include <vector>
#include <QColor>

struct color
{
	int red;
	int green;
	int blue;
	std::string name;
};

extern std::vector<color> colors;
extern std::vector<QColor> basic_colors;
