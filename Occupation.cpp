#include "Enums.h"
#include "Occupation.h"
#include <vector>
#include <string>
#include <iostream>



	//std::string occu_name;
	//PersonalityDim occu_dim;
	//int occu_num;

Occupation::Occupation(std::string name, PersonalityDim dim, int num) {
	occu_name = name;
	occu_dim = dim;
	occu_num = num;
};

std::string Occupation::printFull() {
	std::string y;
	switch (occu_dim)
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
	if (occu_num > 0) {
		return occu_name + ": " + y + " + " + std::to_string(occu_num) +"\n";
	}
	else {
		return occu_name + ": " + y + " - " + std::to_string(occu_num*(-1))+"\n";
	}
	
};