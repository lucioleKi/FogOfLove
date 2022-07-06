#pragma once
#include "Enums.h"
#include <vector>
#include <string>
#include <iostream>



class Feature {
private:
	std::string fea_name;
	PersonalityDim fea_dim;
	int fea_num;
public:
	Feature();
	Feature(std::string name, PersonalityDim dim, int num);
	std::string getName() { return fea_name; };
	PersonalityDim getDim() { return fea_dim; };
	int getNum() { return fea_num; };
	std::string print() { return "(" + fea_name + ", " + std::to_string(fea_dim) + ", " + std::to_string(fea_num) + ")\n"; };
	std::string printFull();
	bool equals(Feature f) { return f.getName() == fea_name; };
};