#pragma once
#include "Enums.h"
#include <vector>
#include <string>
#include <iostream>



class Trait {
private:
	std::string trai_name;
	std::string trai_desc;
	TraitGoalType trai_type;
	PersonalityDim trai_dim;
	int trai_num;
public:
	Trait();
	Trait(std::string name, std::string desc, TraitGoalType type, PersonalityDim dim, int num);
	std::string getName() { return trai_name; };
	std::string getDesc() { return trai_desc; };
	TraitGoalType getType() { return trai_type; };
	PersonalityDim getDim() { return trai_dim; };
	int getNum() { return trai_num; };
	std::string print() { return "(" + trai_name + ": " + trai_desc + "\n" + std::to_string(trai_type) + ", " + std::to_string(trai_dim) + ", " + std::to_string(trai_num) + ")\n"; };
	std::string printFull();
};
