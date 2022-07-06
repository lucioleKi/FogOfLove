#include "Enums.h"
#include "Scene.h"
#include "ReadTxt.h"
#include "Shuffle.h"
#include "Occupation.h"
#include "Feature.h"
#include "ReadEffects.h"
#include <array>
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

std::vector<Feature> importFeatures() {
	std::ifstream fs("feature.txt");
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

std::vector<Chapter> importChapters() {
	std::ifstream fs("chapters.txt");
	std::string line;
	std::vector<Chapter> chapters;
	while (std::getline(fs, line)) {
		std::vector<std::string> info;
		split(line, '\t', info);
		int i = std::stoi(info[0]);
		bool b = (info[1] == "1");
		int l = std::stoi(info[2]);
		int temp = std::stoi(info[3]);
		Deck d1 = (Deck)temp;
		std::vector<Deck> d = { d1 };
		Chapter c = Chapter{ i, b, l, d };
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
	return chapters;
};

std::vector<Scene> importScenes() {
	std::ifstream fs("scenes.txt");
	std::string line;
	std::vector<Scene> scenes;
	while (std::getline(fs, line)) {
		std::vector<std::string> info;
		split(line, '\t', info);
		Scene newScene = generateScene(info);
		scenes.push_back(newScene);
	}
	scenes = importEffects(scenes);
	//scenes = Shuffle(scenes);
	
	return scenes;
};

Scene generateScene(std::vector<std::string> info) {
	int i = std::stoi(info[0]);
	int temp = std::stoi(info[4]);
	Deck d = (Deck)temp;
	char w = info[5][0];
	Scene scene = Scene{ i, d, w };
	scene.setTitle(info[1]);
	scene.setLine(info[2]);
	scene.setExplain(info[3]);
	std::vector<Choice> choices;
	for (int i = 6; i < info.size(); i++) {
		Choice choice = { info[i] };
		choices.push_back(choice);
	}
	scene.setChoices(choices);
	return scene;
};

std::vector<Scene> importEffects(std::vector<Scene> scenes) {
	std::ifstream fs("sceneEffect.txt");
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
