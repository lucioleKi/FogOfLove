#include "SynopsisDestiny.h"
#include "Enums.h"
#include "Scene.h"
#include <vector>
#include <string>
#include <iostream>

Synopsis::Synopsis(std::string t, std::vector<Destiny> d) {
	title = t;
	destinies = d;
	std::vector<Scene> *scenes = 0;
	int starting_hand[3]{};
};

std::string Synopsis::printFull() {
	std::string x = title + "\nDestinies in hand: " ;
	for (int i = 0; i < destinies.size(); i++) {
		x = x + destinies.at(i).getName() + " | ";

	}
	x = x + "\nStarting hand: " + std::to_string(starting_hand[0]) + " Sweet | " + std::to_string(starting_hand[1]) + " Serious | " + std::to_string(starting_hand[2]) + " Drama\n";
	return x;
};

std::vector<Destiny> getDestinies() {
	Destiny dominant = Destiny{ "Dominant", "You will stay in the relationship, but you will only be happy if you have the upper hand. " };
	Destiny equalPartners = Destiny{"Equal Partners", "You will stay in the relationship, but you will only be happy if you are a team of equals. "};
	Destiny loveTeam = Destiny{ "Love Team", "You will stay in the relationship, but your happiness depends on your shared outcomes. "};
	Destiny unconditionalLove = Destiny{ "Unconditional Love", "You will stay in the relationship, but you will only be happy if your partner is happy. "};
	std::vector<Destiny> destinies = { dominant, equalPartners, loveTeam, unconditionalLove };
	return destinies;
};



Synopsis selectSynopsis() {
	std::vector<Destiny> destinies = getDestinies();
	Synopsis s = Synopsis("Sunday Morning Date", destinies);
	s.setStarting(3, 1, 1);
	return s;
};


