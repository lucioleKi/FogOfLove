#pragma once
#include "Enums.h"
#include "CharacterInitial.h"
#include <string>
#include <iostream>

int startGame();
void readyGame();
Character startGender(int num);

std::vector<Trait> startTraits(int num);

Occupation startOccupation(int num);

std::vector<Feature> startFeatures(int num);

void changeName(Character player);