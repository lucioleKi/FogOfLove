#include "Enums.h"
#include "StartChar.h"
#include "CharacterInitial.h"
#include "Trait.h"
#include "Occupation.h"
#include "Feature.h"
#include "PersonalityToken.h"
#include "SynopsisDestiny.h"
#include "Shuffle.h"
#include "ReadTxt.h"
#include <tuple>
#include <vector>
#include <limits>
#include <string>
#include <iostream>

int startGame() {
	
	/*readyGame();
	Character x1 = startGender(1);
	Character x2 = startGender(2);
	std::vector<Trait> traits1 = startTraits(1);
	std::vector<Trait> traits2 = startTraits(2);
	Occupation occu1 = startOccupation(1);
	Occupation occu2 = startOccupation(2);
	std::vector<Feature> features = importFeatures();
	dealCards<std::vector<Feature>> f3 = startFeatures(features);
	std::vector<Feature> fea1 = f3.p1;
	std::vector<Feature> fea2 = f3.p2;
	features = f3.deck;
	std::cout<<features.at(features.size() - 1).printFull();
	std::cout<<features.at(features.size() - 2).printFull();
	PersonalityToken per = PersonalityToken();
	per.changeOccu(1, occu1);
	per.changeOccu(2, occu2);
	per.changeFeature(1, fea1.at(0));
	per.changeFeature(1, fea1.at(1));
	per.changeFeature(1, fea1.at(2));
	per.changeFeature(2, fea2.at(0));
	per.changeFeature(2, fea2.at(1));
	per.changeFeature(2, fea2.at(2));
	changeName(x1);
	changeName(x2);
	std::cout << "Now take a moment to introduce the characters you have created. Tell each other who your characters are in a few sentences.You should still not tell about how you met.\n";
	std::cout << "Press enter to start the game: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	*/
	
	Synopsis plot = selectSynopsis();
	//std::cout<< plot.printFull();
	std::vector<Destiny> d1 = plot.getDestinies();
	std::vector<Destiny> d2 = plot.getDestinies();
	std::vector<Chapter> chapters = importChapters();
	std::vector<Scene> scenes = selectScenes();
	for (int i = 0; i < chapters.size(); i++) {
		Chapter c = chapters.at(i);
		for (int j = 0; j < c.getLength(); j++) {
			
		}
	}
	return 0;
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
	Character player = Character();
	player.setIndex(num);
	std::cout << "Player " << num << ", please select a gender: \n 1 = Female \n 2 = Male \n 3 = Other \n";
	while (1) {
		int x{};
		std::cin >> x;
		if (x == 1) {
			player.setGender(Female);
			std::cout << "\033[2J\033[1;1H";
			return player;
		}
		else if (x == 2) {
			player.setGender(Male);
			std::cout << "\033[2J\033[1;1H";
			return player;
		}else if(x == 3){
			player.setGender(Other);
			std::cout << "\033[2J\033[1;1H";
			return player;
		}
		std::cout << "\nYou entered " << x << ". Please reenter.\n";
	}
};

std::vector<Trait> startTraits(int num) {
	std::cout << "\033[2J\033[1;1H";
	std::cout << "Player " << num << ", please select 3 out of the 5 traits you received below. Your traits cannot be seen by the other player.\n";
	std::vector<Trait> traits = selectTraits();
	std::vector<Trait> chosen;
	for (int j = 1; j < 4; j++) {
		std::cout << "Please select a trait: \n";
		for (int i = 0; i < traits.size(); i++) {
			std::cout << (i + 1) << " = " + traits.at(i).printFull();
		}
		while (1) {
			int x{};
			std::cin >> x;
			if (x > 0 && x < (traits.size() + 1)) {
				chosen.push_back(traits.at(x - 1));
				traits.erase(traits.begin() + (x - 1));
				break;
			}
			else {
				std::cout << "\nYou entered " << x << ". Please reenter.\n";
			}
		}
	}
	
	
	std::cout << chosen.at(0).printFull();
	std::cout << chosen.at(1).printFull();
	std::cout << chosen.at(2).printFull();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//to-do: left-over cards at the bottom
	return chosen;
};




Occupation startOccupation(int num) {
	std::cout << "\033[2J\033[1;1H";
	std::cout << "Player " << num << ", please select 1 out of the 3 occupations you received below. You and your co-player's occupations should be revealed simultaneously.\n";
	std::vector<Occupation> occus = selectOccu();
	std::cout << "1 = " << occus.at(0).printFull();
	std::cout << "2 = " << occus.at(1).printFull();
	std::cout << "3 = " << occus.at(2).printFull();
	while (1) {
		int x{};
		std::cin >> x;
		if (x == 1) {
			std::cout << "Your occupation is " + occus.at(0).getName()+".\n";
			return occus.at(0);
		}
		else if (x == 2) {
			std::cout << "Your occupation is " + occus.at(1).getName()+".\n";
			return occus.at(1);
		}
		else if (x == 3) {
			std::cout << "Your occupation is " + occus.at(2).getName()+".\n";
			return occus.at(2);
		}
		std::cout << "\nYou entered " << x << ". Please reenter.\n";
	}
	//to-do: left-over cards at the bottom
}

dealCards<std::vector<Feature>> startFeatures(std::vector<Feature> deck) {
	//select in turn
	std::cout << "\033[2J\033[1;1H";
	std::cout << "Player 1 and player 2, please select 3 out of the 5 features for your co-player's character. Think of features as the things you first noticed or fell for in your co-player\'s character.\n";
	std::cout << "When choosing, try to tell what it was about this feature that your character fell for (e.g., \"When we first met, I immediately noticed your \'broad shoulders\' and knew you would be the kind of person I\'m looking for\").";
	std::cout << "Don’t make up how you met. This will be done later. Just tell what you noticed about the other.\n";
	std::cout << "You will select features in turn. Player 1 will start first.\n";
	std::vector<Feature> features1 = {deck.at(0), deck.at(1), deck.at(2), deck.at(3), deck.at(4)};
	std::vector<Feature> features2 = { deck.at(5), deck.at(6), deck.at(7), deck.at(8), deck.at(5) };
	std::vector<Feature> chosen1;
	std::vector<Feature> chosen2;
	for (int j = 1; j < 7; j++) {
		if (j % 2 == 1) {
			std::cout << "Player 1, please select a feature for player 2.\n";
			for (int i = 0; i < features2.size(); i++) {
				std::cout << (i + 1) << " = " + features2.at(i).printFull();
			}
			while (1) {
				int x{};
				std::cin >> x;
				if (x > 0 && x < (features2.size() + 1)) {
					chosen2.push_back(features2.at(x - 1));
					features2.erase(features2.begin() + (x - 1));
					break;
				}
				else {
					std::cout << "\nYou entered " << x << ". Please reenter.\n";
				}
			}
		}
		else {
			std::cout << "Player 2, please select a feature for player 1.\n";
			for (int i = 0; i < features1.size(); i++) {
				std::cout << (i + 1) << " = " + features1.at(i).printFull();
			}
			while (1) {
				int x{};
				std::cin >> x;
				if (x > 0 && x < (features1.size() + 1)) {
					chosen1.push_back(features1.at(x - 1));
					features1.erase(features1.begin() + (x - 1));
					break;
				}
				else {
					std::cout << "\nYou entered " << x << ". Please reenter.\n";
				}
			}
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
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//to-do: left-over cards at the bottom
	dealCards<std::vector<Feature>> d { chosen1, chosen2, deck};
	return d;
}

void changeName(Character player) {
	std::cout << "\033[2J\033[1;1H";
	std::cout << "Player " + std::to_string(player.getIndex())+ ", please choose a name that is not your own name. Remember, you are playing fictional characters.\n";
	std::string name;
	std::getline(std::cin, name);
	if (name.length() > 20)
	{
		name.erase(20);
	}
	player.setName(name);
	return;
};

