#pragma once
#include "Enums.h"
#include "Occupation.h"
#include "Feature.h"
#include <string>
#include <iostream>

class PersonalityToken {
private:
	int personality1[12];
	int personality2[12];
	int personalityShared[12];
public:
	PersonalityToken();
	int get1(int position) { return personality1[position]; };
	int get2(int position) { return personality2[position]; };
	int getShared(int position) { return personalityShared[position]; };
	void change(int arr, int position, int num);
	void changeOccu(int player, Occupation occu);
	void changeFeature(int player, Feature fea);
};