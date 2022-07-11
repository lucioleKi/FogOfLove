#pragma once
#include "Enums.h"
#include "Occupation.h"
#include "Feature.h"
#include <vector>
#include <string>
#include <iostream>

class PersonalityToken {
private:
	std::vector<int> personality1{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	std::vector<int> personality2{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::vector<int> personalityShared{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::vector<std::string> text{ "Discipline", "Curiosity", "Extroversion", "Sensitivity", "Gentleness", "Sincerity" };
public:
	PersonalityToken() {
		std::vector<int> personality1{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		std::vector<int> personality2{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		std::vector<int> personalityShared{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		std::vector<std::string> text{ "Discipline", "Curiosity", "Extroversion", "Sensitivity", "Gentleness", "Sincerity" };
	};
	std::vector<int> getArray1() { return personality1; };
	std::vector<int> getArray2() { return personality2; };
	std::vector<int> getArrayShared() { return personalityShared; };
	int get1(int position) { return personality1.at(position); };
	int get2(int position) { return personality2.at(position); };
	int getShared(int position) { return personalityShared.at(position); };
	void change(int arr, int position, int num);
	void changeOccu(int player, Occupation occu);
	void changeFeature(int player, Feature fea);
	std::string printFull();
};