#pragma once
#include "Enums.h"
#include "Session.h"
#include "Scene.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

Session resolveEffectsP(Session game, int turn, Scene scene, int choice1);

Session resolveEffectsB(Session game, int turn, Scene scene, int choice1, int choice2);

Session resolveSatis(Session game, int chooser, Choice c);

Session resolveAddi(Session game, int turn, Scene scene, int c1, int c2);

int matchChoice(Scene scene, int c1, int c2, int player);

std::vector<std::string> match2(int c1, int c2, int player);