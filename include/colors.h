#pragma once

#include <string>
#include <vector>

struct color
{
	int red;
	int green;
	int blue;
	std::string name;
};

extern std::vector<color> colors;
