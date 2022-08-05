#pragma once
#include "Enums.h"
#include "Scene.h"
#include "Feature.h"
#include "Occupation.h"
#include "Trait.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

void split(const std::string& s, char delim, std::vector<std::string>& elems);

std::map<std::string, std::string> importVocab(std::string fileName);

std::vector<Feature> importFeatures(std::string fileName);
std::vector<Occupation> importOccus(std::string fileName);
std::vector<Trait> importTraits(std::string fileName);


std::vector<Chapter> importChapters(std::string fileName, std::string effects);

std::vector<Scene> importScenes(std::string fileName, std::string effects);
Scene generateScene(std::vector<std::string> info);

std::vector<Scene> importEffects(std::vector<Scene> scenes, std::string fileName);
std::vector<Chapter> importChapterE(std::vector<Chapter> chapters, std::string fileName);
