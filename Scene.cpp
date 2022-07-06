#include "Scene.h"
#include "Enums.h"
#include "ReadTxt.h"
#include <string>
#include <iostream>

Chapter::Chapter(int i, bool b, int l, std::vector<Deck> d) {
	index = i;
	both = b;
	length = l;
	drawFrom = d;
}

std::string Chapter::printFull() {
	std::string x = "Chapter " + std::to_string(index) + "\n" + title + "\n";
	if (both) {
		x = x + "Both Choose\n";
	}
	else {

	}
	char alphabet[] = "ABCD";
	for (int i = 0; i < choices.size(); i++) {
		x = x + alphabet[i] + " = " + choices.at(i).getDescription() + "\n";
	}
	x = x + "Length: " + std::to_string(length) + "\n";
	for (int i = 0; i < drawFrom.size(); i++) {
		x = x + "Draw cards from: ";
		switch (drawFrom.at(0)) {
		case Sweet:
			x = x + "Sweet\n";
			break;
		case Serious:
			x = x + "Serious\n";
			break;
		case Drama:
			x = x + "Drama\n";
			break;
		}

	}
	return x;
};

Scene::Scene(int i, Deck d, char w) {
	index = i;
	deck = d;
	whoChoose = w;
}

std::string Scene::printFull() {
	std::string x = title + "\n"+line+"\n";
	if (whoChoose == 'B') {
		x = x + "Both choose\n";
	}
	else {
		x = x + "Partner chooses\n";
	}
	if (explain_choices != "N") {
		x = x + "(" + explain_choices + ")\n";
	}
	char alphabet[] = "ABCD";
	for (int i = 0; i < choices.size(); i++) {
		x = x + alphabet[i] + " = " + choices.at(i).printFull() + "\n";
	}
	for (int i = 0; i < additionals.size(); i++) {
		for (int j = 0; j < additionals.at(i).getCode().size(); j++) {
			x = x + additionals.at(i).getCode().at(j) + ", ";
		}
		x = x + "\n";
	}
	x = x + "Deck: ";
	switch (deck) {
	case Sweet:
		x = x + "Sweet\n";
		break;
	case Serious:
		x = x + "Serious\n";
		break;
	case Drama:
		x = x + "Drama\n";
		break;
	}
	

	return x;
}

std::string Choice::printFull() {
	std::string x = description + "\n";
	for (int i = 0; i < dims.size(); i++) {
		switch (dims.at(i))
		{
		case Discipline:
			x = x + "Discipline";
			break;
		case Curiosity:
			x = x + "Curiosity";
			break;
		case Extroversion:
			x = x + "Extroversion";
			break;
		case Sensitivity:
			x = x + "Sensitivity";
			break;
		case Gentleness:
			x = x + "Gentleness";
			break;
		case Sincerity:
			x = x + "Sincerity";
			break;
		}
		if (nums.at(i) > 0) {
			x = x + " + " + std::to_string(nums.at(i)) + "\n";
		}
		else {
			x = x + " - " + std::to_string(nums.at(i)*(-1)) + "\n";
		}
	}

	if (choser_satis > 0) {
		x = x + "Chooser + " + std::to_string(choser_satis) + "\n";

	}
	else if (choser_satis < 0) {
		x = x + "Chooser - " + std::to_string(choser_satis*(-1)) + "\n";
	}

	if (other_satis > 0) {
		x = x + "Other + " + std::to_string(choser_satis) + "\n";

	}
	else if (choser_satis < 0) {
		x = x + "Other - " + std::to_string(choser_satis * (-1)) + "\n";
	}

	for (int i = 0; i < code.size(); i++) {
		x = x + code.at(i)+", ";
	}
	return x;
};


std::vector<Scene> selectScenes() {
	std::vector<Scene> scenes = importScenes();

	/*std::cout << scenes.at(0).printFull();
	std::cout << scenes.at(1).printFull();
	std::cout << scenes.at(2).printFull();
	std::cout << scenes.at(3).printFull();
	std::cout << scenes.at(4).printFull();
	std::cout << scenes.at(5).printFull();
	*/
	return scenes;
}
