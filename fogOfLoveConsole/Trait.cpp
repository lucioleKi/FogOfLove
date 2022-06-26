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
	return trai_name + ": " + trai_desc + "Trait goal: " + x + " " + y + " balance is " + std::to_string(trai_num) + " or more.\n";
};

std::vector<Trait> selectTraits() {
	Trait trai1 = Trait{ "Patient",  "Able to remain calm and not become annoyed while experiencing delays and problems. ", Individual, Sincerity, 3};
	Trait trai2 = Trait{ "Promiscuous", "Having an unselective and casual approach to engaging in sexual relationships. ", Individual, Curiosity, 1};
	Trait trai3 = Trait{ "Jealous", "Showing envious resentment of others\' success. Being suspicious and possessive towards others. ", Individual, Sensitivity, 3 };
	Trait trai4 = Trait{ "Task-oriented", "Concerned with one\'s activities and goals rather than other people. ", Shared, Sincerity, -5};
	Trait trai5 = Trait{"Perfectionist", "Refusing to accept anything less than perfection. Demands the highest standards possible. ", Shared, Discipline, 5};
	Trait trai6 = Trait{"Just", "Having a strong sense of what\'s right and what\'s wrong. ", Shared, Sincerity, 5};
	std::vector<Trait> traits3{trai1, trai2, trai3, trai4, trai5};
	return traits3;
}