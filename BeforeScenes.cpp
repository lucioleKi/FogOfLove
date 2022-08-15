#include "Enums.h"
#include "CharacterInitial.h"
#include "Trait.h"
#include "Occupation.h"
#include "Feature.h"
#include "PersonalityToken.h"
#include "SynopsisDestiny.h"
#include "Shuffle.h"
#include "ReadTxt.h"
#include <vector>
#include <limits>
#include <string>
#include <iostream>
#include <conio.h>

//https://stackoverflow.com/questions/24708700/c-detect-when-user-presses-arrow-key
#define KEY_UP 72       //Up arrow character
#define KEY_DOWN 80    //Down arrow character
#define KEY_ENTER '\r'//Enter key charatcer
int select(int numChoices) {
	int selected = 0;    //Keeps track of which option is selected.
	 //numChoices The number of choices we have.
	bool selecting = true;//True if we are still waiting for the user to press enter.
	bool updated = false;//True if the selected value has just been updated.
	std::cout << "Option 1 is selected. Press up/down to change. Press Enter to confirm.";
	//Output options

	//std::cout << "A. Option 1\n";
	//std::cout << "B. Option 2\n";

	char c; //Store c outside of loop for efficiency.
	while (selecting) { //As long as we are selecting...
		switch ((c = _getch())) { //Check value of the last inputed character.
		case KEY_UP:
			if (selected > 0) { //Dont decrement if we are at the first option.
				--selected;
				updated = true;
			}
			break;
		case KEY_DOWN:
			if (selected < numChoices - 1) { //Dont increment if we are at the last option.
				++selected;
				updated = true;
			}
			break;
		case KEY_ENTER:
			//We are done selecting the option.
			selecting = false;
			break;
		default: break;
		}
		if (updated) { //Lets us know what the currently selected value is.
			std::cout << "\r" << "Option " << (selected + 1) << " is selected. Press up/down to change. Press Enter to confirm.";
			updated = false;
		}
	}
	//Lets us know what we ended up selecting.
	std::cout << '\n';
	return selected;
};

void readyGame() {
	std::cout << "Welcome to Fog of Love - Romandic Comedy as a Board Game\n";

	std::cout << "This application is made by ki. It does NOT include the tutorial. You and your co-player need to know the rules beforehand.\n";
	std::cout << "Press enter to start creating the characters: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return;
};



Character startGender(int num) {
	std::cout << "\033[2J\033[1;1H";
	Character player = Character(num);
	player.setSatisfaction(0);
	std::cout << "Player " << num << ", please select a gender: \n 1 = Female \n 2 = Male \n 3 = Other \n";

		int x = select(3);
		if (x == 0) {
			player.setGender(Female);
			std::cout << "\033[2J\033[1;1H";
			return player;
		}
		else if (x == 1) {
			player.setGender(Male);
			std::cout << "\033[2J\033[1;1H";
			return player;
		}
		else if (x == 2) {
			player.setGender(Other);
			std::cout << "\033[2J\033[1;1H";
			return player;
		}
};

dealCards<std::vector<Trait>> startTraits(std::vector<Trait> deck) {
	std::cout << "\033[2J\033[1;1H";
	
	std::vector<Trait> trait1 = {deck.at(0), deck.at(1), deck.at(2), deck.at(3), deck.at(4)};
	std::vector<Trait> trait2 = {deck.at(5), deck.at(6), deck.at(7), deck.at(8), deck.at(9)};
	std::vector<Trait> chosen1, chosen2;
	std::cout << "Player 1, please select 3 out of the 5 traits you received below. Your traits cannot be seen by the other player.\n";

	deck.erase(deck.begin(), deck.begin() + 10);
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < trait1.size(); i++) {
			std::cout << trait1.at(i).printFull();
		}
		int c1 = select(trait1.size());
		chosen1.push_back(trait1.at(c1));
		trait1.erase(trait1.begin() + c1);
	}
	deck.push_back(trait1.at(0));
	deck.push_back(trait1.at(1));
	std::cout << "\033[2J\033[1;1H";
	std::cout << "Player 2, please select 3 out of the 5 traits you received below. Your traits cannot be seen by the other player.\n";
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < trait2.size(); i++) {
			std::cout << trait2.at(i).printFull();
		}
		int c2 = select(trait2.size());
		chosen2.push_back(trait2.at(c2));
		trait2.erase(trait2.begin() + c2);
	}
	deck.push_back(trait2.at(0));
	deck.push_back(trait2.at(1));
	std::cout << "Player 1's traits are " + chosen1.at(0).getName()+", " + chosen1.at(1).getName()+", " + chosen1.at(2).getName() + ".\n";
	std::cout << "Player 2's traits are " + chosen2.at(0).getName() + ", " + chosen2.at(1).getName() + ", " + chosen2.at(2).getName() + ".\n";
	dealCards<std::vector<Trait>> d{ deck , chosen1, chosen2 };
	return d;
};




dealCards<std::vector<Occupation>> startOccupation(std::vector<Occupation> deck) {
	std::cout << "\033[2J\033[1;1H";
	std::cout << "Player 1, please select 1 out of the 3 occupations you received below. You and your co-player's occupations will be revealed simultaneously.\n";
	std::vector<Occupation> occus1 = { deck.at(0), deck.at(1), deck.at(2) };
	std::vector<Occupation> occus2 = { deck.at(3), deck.at(4), deck.at(5) };
	deck.erase(deck.begin(), deck.begin() + 6);
	std::vector<Occupation> chosen1, chosen2;
	for (int i = 0; i < 3; i++) {
		std::cout << occus1.at(i).printFull();
	}
	int c1 = select(3);
	chosen1.push_back(occus1.at(c1));
	occus1.erase(occus1.begin() + c1);
	deck.push_back(occus1.at(0));
	deck.push_back(occus1.at(1));
	std::cout << "Player 2, please select 1 out of the 3 occupations you received below. You and your co-player's occupations will be revealed simultaneously.\n";
	for (int i = 0; i < 3; i++) {
		std::cout << occus2.at(i).printFull();
	}
	int c2 = select(3);
	chosen2.push_back(occus2.at(c2));
	occus2.erase(occus2.begin() + c2);
	deck.push_back(occus2.at(0));
	deck.push_back(occus2.at(1));
	std::cout << "Player 1's occupation is " + chosen1.at(0).getName() + ".\n";
	std::cout << "Player 2's occupation is " + chosen2.at(0).getName() + ".\n";
	dealCards<std::vector<Occupation>> d{ deck , chosen1, chosen2 };
	return d;
};

dealCards<std::vector<Feature>> startFeatures(std::vector<Feature> deck) {
	//select in turn
	std::cout << "\033[2J\033[1;1H";
	std::cout << "Player 1 and player 2, please select 3 out of the 5 features for your co-player's character. Think of features as the things you first noticed or fell for in your co-player\'s character.\n";
	std::cout << "When choosing, try to tell what it was about this feature that your character fell for (e.g., \"When we first met, I immediately noticed your \'broad shoulders\' and knew you would be the kind of person I\'m looking for\").";
	std::cout << "Don’t make up how you met. This will be done later. Just tell what you noticed about the other.\n";
	std::cout << "You will select features in turn. Player 1 will start first.\n";
	std::vector<Feature> features1 = { deck.at(0), deck.at(1), deck.at(2), deck.at(3), deck.at(4) };
	std::vector<Feature> features2 = { deck.at(5), deck.at(6), deck.at(7), deck.at(8), deck.at(9) };
	deck.erase(deck.begin(), deck.begin() + 10);
	std::vector<Feature> chosen1;
	std::vector<Feature> chosen2;
	for (int j = 1; j < 7; j++) {
		if (j % 2 == 1) {
			std::cout << "Player 1, please select a feature for player 2.\n";
			for (int i = 0; i < features2.size(); i++) {
				std::cout << (i + 1) << " = " + features2.at(i).printFull();
			}
			int c2 = select(features2.size());
			chosen2.push_back(features2.at(c2));
			features2.erase(features2.begin() + (c2));
		}
		else {
			std::cout << "Player 2, please select a feature for player 1.\n";
			for (int i = 0; i < features1.size(); i++) {
				std::cout << (i + 1) << " = " + features1.at(i).printFull();
			}
			int c1 = select(features1.size());
			chosen1.push_back(features1.at(c1));
			features1.erase(features1.begin() + (c1));
		}


	}
	deck.push_back(features1.at(0));
	deck.push_back(features1.at(1));
	deck.push_back(features2.at(0));
	deck.push_back(features2.at(1));
	std::cout << "Player 1 Features:\n";
	std::cout << chosen1.at(0).printFull();
	std::cout << chosen1.at(1).printFull();
	std::cout << chosen1.at(2).printFull();
	std::cout << "Player 2 Features: \n";
	std::cout << chosen2.at(0).printFull();
	std::cout << chosen2.at(1).printFull();
	std::cout << chosen2.at(2).printFull();
	//to-do: left-over cards at the bottom
	dealCards<std::vector<Feature>> d{ deck, chosen1, chosen2 };
	return d;
};

Character changeName(Character player) {
	std::cout << "\033[2J\033[1;1H";
	std::cout << "Player " + std::to_string(player.getIndex()) + ", please choose a name that is not your own name. Remember, you are playing fictional characters.\n";
	std::string name;
	
	std::cin>>name;
	player.setName(name);
	//player.setName("Kelly");
	return player;
};


