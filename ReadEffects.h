#pragma once
#include "Enums.h"
#include "Scene.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

struct PT {
	int in;
	Choice c;
	std::vector<std::string> effects{};
};

Scene readEffects(Scene s, std::vector<std::string> effects);
Chapter readEffectsC(Chapter s, std::vector<std::string> effects);
PT readPT(int begin, int end, Choice c, std::vector<std::string> effects);

PT readChoser(int begin, int index, Choice c, std::vector<std::string> effects);