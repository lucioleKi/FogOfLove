#include "Enums.h"
#include "CharacterInitial.h"
#include <string>
#include <iostream>

Character::Character(int index) {
	char_index = index;
	char_satisfaction = 0;
};

Character::Character(int index, std::string name, Gender gender, int satisfaction) {
	char_index = index;
	char_name = name;
	char_gender = gender;
	char_satisfaction = satisfaction;
};

void Character::setIndex(int index) {
	char_index = index;
};

void Character::setName(std::string name) {
	char_name = name;
};
void Character::setGender(Gender gender) {
	char_gender = gender;
};
void Character::setSatisfaction(int satisfaction) {
	char_satisfaction = char_satisfaction + satisfaction;
	if (char_satisfaction < 0) {
		char_satisfaction = 0;
	}
};
