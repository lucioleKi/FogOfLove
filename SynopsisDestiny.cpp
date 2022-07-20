#include "SynopsisDestiny.h"
#include "Enums.h"
#include "Scene.h"
#include <vector>
#include <string>
#include <iostream>

Synopsis::Synopsis(std::string t, std::vector<Destiny> d) {
	title = t;
	destinies = d;
	std::vector<Scene> scenes;
	std::vector<int> starting_hand;
};

std::string Synopsis::printFull() {
	std::string x = title + "\nDestinies in hand: " ;
	for (int i = 0; i < destinies.size(); i++) {
		x = x + destinies.at(i).getName() + " | ";

	}
	x = x + "\nStarting hand: " + std::to_string(starting_hand[0]) + " Sweet | " + std::to_string(starting_hand[1]) + " Serious | " + std::to_string(starting_hand[2]) + " Drama\n";
	return x;
};

std::string Destiny::printFull() {
	std::string x = name + ". " + description + "\n";
	return x;
}

std::vector<Destiny> getDestinies() {
	Destiny dominant = Destiny{ "DOMINANT", "You will stay in the relationship, but you will only be happy if you have the upper hand. ", true};
	Destiny equalPartners = Destiny{"EQUAL PARTNERS", "You will stay in the relationship, but you will only be happy if you are a team of equals. ", true};
	Destiny loveTeam = Destiny{ "LOVE TEAM", "You will stay in the relationship, but your happiness depends on your shared outcomes. ", true};
	Destiny unconditionalLove = Destiny{ "UNCONDITIONAL LOVE", "You will stay in the relationship, but you will only be happy if your partner is happy. ", true};
	Destiny honorableExit = Destiny{ "HONORABLE EXIT", "You break up, because you weren\'t meant for each other." ,false};
	Destiny heartbreaker = Destiny{ "HEARTBREAKER", "You break up, because that\'s what you do.", false};
	std::vector<Destiny> destinies = { dominant, equalPartners, loveTeam, unconditionalLove, honorableExit, heartbreaker };
	return destinies;
};





Synopsis selectSynopsis() {
	std::vector<Destiny> destinies = getDestinies();
	Synopsis s = Synopsis("Sunday Morning Date", destinies);
	s.setStarting(3, 1, 1);
	return s;
};


