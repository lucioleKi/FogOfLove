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
public:
	Destiny(std::string n, std::string d) { name = n; description = d; };
	std::string getName() { return name; };
	std::string getDescription() { return description; };
	void setName(std::string n) { name = n; };
	void setDescription(std::string d) { description = d; };
};

class Synopsis{
private:
	std::string title;
	std::vector<Destiny> destinies;
	std::vector<Scene> scenes;
	int starting_hand[3];
public:
	Synopsis(std::string t, std::vector<Destiny> d);
	std::string getTitle() { return title; };
	std::vector<Destiny> getDestinies() { return destinies; };
	std::vector<Scene> getScenes() { return scenes; };
	int getStarting() { return *starting_hand; };
	void setTitle(std::string t) { title = t; };
	void setDestinies(std::vector<Destiny> d) { destinies = d; };
	void setScenes(std::vector<Scene> s) { scenes = s; };
	void setStarting(int s1, int s2, int s3) { starting_hand[0] = s1; starting_hand[1] = s2; starting_hand[2] = s3; };
	std::string printFull();
};

std::vector<Destiny> getDestinies();
Synopsis selectSynopsis();
