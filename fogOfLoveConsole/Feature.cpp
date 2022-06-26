#include "Enums.h"
#include "Feature.h"
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

std::vector<Feature> selectFeatures() {
	Feature fea1 = Feature{ "Odd socks", Discipline, -1};
	Feature fea2 = Feature{ "Jiggling legs", Sensitivity, 1};
	Feature fea3 = Feature{ "Worn-out jewelry", Curiosity, -1};
	Feature fea4 = Feature{ "Androgynous", Gentleness, 1};
	Feature fea5 = Feature{ "Perfect teeth", Discipline, 1};
	Feature fea6 = Feature{ "Body odor", Discipline, -1};
	std::vector<Feature> features{ fea1, fea2, fea3, fea4, fea5 };
	return features;
}