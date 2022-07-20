#pragma once
#include "Enums.h"
#include "StartChar.h"
#include "CharacterInitial.h"
#include "Trait.h"
#include "Occupation.h"
#include "Feature.h"
#include "PersonalityToken.h"
#include "SynopsisDestiny.h"
#include "Shuffle.h"
#include "ReadTxt.h"
#include <vector>
#include <limits>
#include <string>
#include <iostream>
#include <conio.h>

int select(int numChoices);
void readyGame();

Character startGender(int num);

std::vector<Trait> startTraits(int num);

dealCards<std::vector<Occupation>> startOccupation(std::vector<Occupation> deck);

dealCards<std::vector<Feature>> startFeatures(std::vector<Feature> deck);

Character changeName(Character player);