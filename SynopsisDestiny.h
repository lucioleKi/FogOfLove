#pragma once
#include "Enums.h"
#include "Scene.h"
#include <vector>
#include <string>
#include <iostream>

class Destiny {
private:
	std::string name;
	std::string description;
	bool inHand;
public:
	Destiny(std::string n, std::string d, bool i) { name = n; description = d; inHand = i; };
	std::string getName() { return name; };
	std::string getDescription() { return description; };
	std::string printFull();
	bool getIn() { return inHand; };
	void setName(std::string n) { name = n; };
	void setDescription(std::string d) { description = d; };
	void changeIn() { inHand = !inHand; };
};

class Synopsis{
private:
	std::string title;
	std::vector<Destiny> destinies;
	std::vector<Scene> scenes;
	std::vector<int> starting_hand;
public:
	Synopsis(std::string t, std::vector<Destiny> d);
	std::string getTitle() { return title; };
	std::vector<Destiny> getDestinies() { return destinies; };
	std::vector<Scene> getScenes() { return scenes; };
	std::vector<int> getStarting() { return starting_hand; };
	void setTitle(std::string t) { title = t; };
	void setDestinies(std::vector<Destiny> d) { destinies = d; };
	void setScenes(std::vector<Scene> s) { scenes = s; };
	void setStarting(int s1, int s2, int s3) { starting_hand.push_back(s1); starting_hand.push_back(s2); starting_hand.push_back(s3); };
	std::string printFull();
};

std::vector<Destiny> getDestinies();
Synopsis selectSynopsis();
