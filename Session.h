#pragma once
#include "Enums.h"
#include "Scene.h"
#include "CharacterInitial.h"
#include "PersonalityToken.h"
#include "SynopsisDestiny.h"

struct Session {
	Character x1;
	Character x2;
	std::vector<Trait> traits;
	std::vector<Trait> traits1;
	std::vector<Trait> traits2;
	std::vector<Occupation> occu;
	Occupation occu1;
	Occupation occu2;
	std::vector<Feature> features;
	std::vector<Feature> fea1;
	std::vector<Feature> fea2;
	PersonalityToken per;
	Synopsis plot;
	std::vector<Destiny> d1;
	std::vector<Destiny> d2;
	std::vector<Chapter> chapters;
	std::vector<Scene> sweetS;
	std::vector<Scene> seriousS;
	std::vector<Scene> dramaS;
	std::vector<Scene> hand1;
	std::vector<Scene> hand2;
	std::vector<std::string> carryOver;
	std::vector<Scene> secret1;
	std::vector<Scene> secret2;
};
