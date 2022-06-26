#pragma once
#include "Enums.h"
#include <vector>
#include <string>
#include <iostream>


class Occupation{
private:
	std::string occu_name;
	PersonalityDim occu_dim;
	int occu_num;
public:
	Occupation(std::string name, PersonalityDim dim, int num);
	std::string getName() { return occu_name; };
	PersonalityDim getDim() { return occu_dim; };
	int getNum() { return occu_num; };
	std::string print() { return "(" + occu_name +", " + std::to_string(occu_dim) + ", " + std::to_string(occu_num) + ")\n"; };
	std::string printFull();
};

std::vector<Occupation> selectOccu();

