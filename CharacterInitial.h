#pragma once
#include "Enums.h"
#include "Occupation.h"
#include "Trait.h"
#include "Feature.h"
#include <string>
#include <iostream>

class Character {
private:
	int char_index;
	std::string char_name;
	Gender char_gender;
	int char_satisfaction;
public:
	Character(int index);
	Character(int index,std::string name, Gender gender, int satisfaction);
	int getIndex() { return char_index; };
	std::string getName() { return char_name; };
	Gender getGender() { return char_gender; };
	int getSatisfaction() { return char_satisfaction; };
	void setIndex(int index);
	void setName(std::string name);
	void setGender(Gender gender);
	void setSatisfaction(int satisfaction);
	std::string print() { return "(" + std::to_string(char_index) + ", " + char_name + ", " + std::to_string(char_gender) + ", " + std::to_string(char_satisfaction) + ")\n"; };
};
