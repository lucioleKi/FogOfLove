#pragma once
#include "Enums.h"
#include "CharacterInitial.h"
#include "Shuffle.h"
#include <tuple>
#include <string>
#include <iostream>

int startGame();
void readyGame();
Character startGender(int num);

std::vector<Trait> startTraits(int num);

Occupation startOccupation(int num);

dealCards<std::vector<Feature>> startFeatures(std::vector<Feature> deck);

void changeName(Character player);