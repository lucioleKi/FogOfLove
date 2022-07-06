#include "Enums.h"
#include "Feature.h"
#include "ReadTxt.h"
#include <vector>
#include <string>
#include <iostream>

Feature::Feature() {

};

Feature::Feature(std::string name, PersonalityDim dim, int num) {
	fea_name = name;
	fea_dim = dim;
	fea_num = num;
};

std::string Feature::printFull() {
	std::string y;
	switch (fea_dim)
	{
	case Discipline:
		y = "Discipline";
		break;
	case Curiosity:
		y = "Curiosity";
		break;
	case Extroversion:
		y = "Extroversion";
		break;
	case Sensitivity:
		y = "Sensitivity";
		break;
	case Gentleness:
		y = "Gentleness";
		break;
	case Sincerity:
		y = "Sincerity";
		break;
	}
	if (fea_num > 0) {
		return fea_name + ": " + y + " + " + std::to_string(fea_num) + "\n";
	}
	else {
		return fea_name + ": " + y + " - " + std::to_string(fea_num * (-1)) + "\n";
	}
};

