#include "Enums.h"
#include "Scene.h"
#include "ReadTxt.h"
#include "Shuffle.h"
#include "Occupation.h"
#include "Feature.h"
#include "ReadEffects.h"
#include <array>
#include <map>
#include <vector>
#include <string>
#include <iostream>

void split(const std::string& s, char delim, std::vector<std::string>& elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
};

std::map<std::string, std::string> importVocab(std::string fileName) {

	std::ifstream fs(fileName);
	std::string line;
	std::map<std::string, std::string> pairs;
	while (std::getline(fs, line)) {
		std::vector<std::string> info;
		split(line, '\t', info);
		pairs.insert({ info[0], info[1] });
	}
	return pairs;
};

std::vector<Feature> importFeatures(std::string fileName) {
	std::ifstream fs(fileName);
	std::string line;
	std::vector<Feature> features;
	while (std::getline(fs, line)) {
		std::vector<std::string> info;
		split(line, '\t', info);
		int temp = std::stoi(info[1]);
		PersonalityDim p = (PersonalityDim)temp;
		int number = std::stoi(info[2]);
		Feature o = Feature{ info[0], p, number};
		features.push_back(o);
	}
	features = Shuffle(features);
	return features;
};

std::vector<Occupation> importOccus(std::string fileName) {
	std::ifstream fs(fileName);
	std::string line;
	std::vector<Occupation> occus;
	while (std::getline(fs, line)) {
		std::vector<std::string> info;
		split(line, '\t', info);
		int temp = std::stoi(info[1]);
		PersonalityDim p = (PersonalityDim)temp;
		int number = std::stoi(info[2]);
		Occupation o = Occupation{ info[0], p, number };
		occus.push_back(o);
	}
	occus = Shuffle(occus);
	return occus;
};

std::vector<Trait> importTraits(std::string fileName) {
	std::ifstream fs(fileName);
	std::string line;
	std::vector<Trait> traits;
	while (std::getline(fs, line)) {
		std::vector<std::string> info;
		split(line, '\t', info);
		int goalType = std::stoi(info[2]);
		TraitGoalType g = (TraitGoalType)goalType;
		int temp = std::stoi(info[3]);
		PersonalityDim p = (PersonalityDim)temp;
		int number = std::stoi(info[4]);
		Trait t = Trait{info[0], info[1], g, p, number};
		traits.push_back(t);
	}
	traits = Shuffle(traits);
	return traits;
};

std::vector<Chapter> importChapters(std::string fileName, std::string effects) {
	std::ifstream fs(fileName);
	std::string line;
	std::vector<Chapter> chapters;
	while (std::getline(fs, line)) {
		std::vector<std::string> info;
		split(line, '\t', info);
		int i = std::stoi(info[0]);
		
		int l = std::stoi(info[2]);
		int temp = std::stoi(info[3]);
		Deck d1 = (Deck)temp;
		std::vector<Deck> d = { d1 };
		Chapter c = Chapter{ i, 'B', l, d};
		c.setTitle(info[4]);
		c.setLine(info[5]);
		std::vector<Choice> choices;
		for (int i = 6; i < info.size(); i++) {
			Choice choice = { info[i] };
			choices.push_back(choice);
		}
		c.setChoices(choices);
		chapters.push_back(c);
	}
	chapters = importChapterE(chapters, effects);
	std::map<std::string, std::string> vocab = importVocab("vocabulary.txt");
	chapters = Vocab(chapters, vocab);
	return chapters;
};

std::vector<Scene> importScenes(std::string fileName, std::string effects) {
	std::ifstream fs(fileName);
	std::string line;
	std::vector<Scene> scenes;
	while (std::getline(fs, line)) {
		std::vector<std::string> info;
		split(line, '\t', info);
		Scene newScene = generateScene(info);
		scenes.push_back(newScene);
	}
	scenes = importEffects(scenes, effects);
	std::map<std::string, std::string> vocab = importVocab("vocabulary.txt");
	scenes = Vocab(scenes, vocab);
	scenes = Shuffle(scenes);
	return scenes;
};

Scene generateScene(std::vector<std::string> info) {
	int i = std::stoi(info[0]);
	int temp = std::stoi(info[4]);
	Deck d = (Deck)temp;
	char w = info[5][0];
	Scene scene = Scene{ i, d, w };
	scene.setTitle(info[1]);
	if (info[2] == "N") {
		scene.setLine("");
	}
	else {
		scene.setLine(info[2]);
	}
	
	if (info[3] == "N") {
		scene.setExplain("");
	}
	else {
		scene.setExplain(info[3]);
	}
	if (w == 'B'||w == 'P'||w =='C'||w =='S'||w =='E'||w =='N'||w == 'R') {
		std::vector<Choice> choices;
		for (int i = 6; i < info.size(); i++) {
			Choice choice = { info[i] };
			choices.push_back(choice);
		}
		scene.setChoices(choices);
	}
	
	
	return scene;
};

std::vector<Scene> importEffects(std::vector<Scene> scenes, std::string fileName) {
	std::ifstream fs(fileName);
	std::string line;
	int index = 0;
	while (std::getline(fs, line)) {
		std::vector<std::string> info;
		split(line, '\t', info);
		int i = std::stoi(info[0]);
		scenes.at(i-1) = readEffects(scenes.at(i-1), info);
		index++;
	}
	return scenes;
};

std::vector<Chapter> importChapterE(std::vector<Chapter> chapters, std::string fileName) {
	std::ifstream fs(fileName);
	std::string line;
	int index = 0;
	while (std::getline(fs, line)) {
		std::vector<std::string> info;
		split(line, '\t', info);
		int i = std::stoi(info[0]);
		chapters.at(i - 1) = readEffectsC(chapters.at(i - 1), info);
		index++;
	}
	return chapters;
};