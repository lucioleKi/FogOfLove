#include "Enums.h"
#include "Trait.h"
#include <vector>
#include <string>
#include <iostream>

Trait::Trait() {
	
};

Trait::Trait(std::string name, std::string desc, TraitGoalType type, PersonalityDim dim, int num) {
	trai_name = name;
	trai_desc = desc;
	trai_type = type;
	trai_dim = dim;
	trai_num = num;
};

std::string Trait::printFull() {
	std::string x, y;
	switch (trai_type)
	{
	case Individual:
		x = "Individual";
		break;
	case Shared:
		x = "Shared";
		break;
	}
	switch (trai_dim)
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
	return trai_name + ": " + trai_desc + " Trait goal: " + x + " " + y + " balance is " + std::to_string(trai_num) + " or more.\n";
};
