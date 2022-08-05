#include "Scene.h"
#include "Enums.h"
#include "ReadTxt.h"
#include <string>
#include <iostream>

Chapter::Chapter(int i, char b, int l, std::vector<Deck> d) {
	index = i;
	whoChoose = b;
	length = l;
	drawFrom = d;
}

std::string Chapter::printFull() {
	std::string x = "Chapter " + std::to_string(index) + "\n" + title + "\n";
	if (whoChoose=='B') {
		x = x + "Both Choose\n";
	}
	else {

	}
	char alphabet[] = "ABCD";
	for (int i = 0; i < choices.size(); i++) {
		x = x + alphabet[i] + " = " + choices.at(i).printFull();
	}
	if (additionals.size() > 0) {
		x = x + "ADDITIONAL EFFECTS\n";
	}
	for (int i = 0; i < additionals.size(); i++) {
		x = x + additionals.at(i).getFull() + "\n";
		//for (int j = 0; j < additionals.at(i).getCode().size(); j++) {

			//x = x + additionals.at(i).getCode().at(j) + ", ";
		//}
		x = x + "\n";
	}
	x = x + "Length: " + std::to_string(length) + "\n";
	for (int i = 0; i < drawFrom.size(); i++) {
		x = x + "Draw cards from: ";
		switch (drawFrom.at(0)) {
		case Sweet:
			x = x + "Sweet\n\n";
			break;
		case Serious:
			x = x + "Serious\n\n";
			break;
		case Drama:
			x = x + "Drama\n\n";
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
	else if(whoChoose == 'P') {
		x = x + "Partner chooses\n";
	}
	else if (whoChoose == 'S') {
		x = x + "Situation\n";
	}
	else if (whoChoose == 'E') {
		x = x + "Special Effect\n";
	}
	else if (whoChoose == 'T' || whoChoose == 'C') {
		x = x + "Secret\n";
	}
	else if (whoChoose == 'V') {
		x = x + "Reveal Secret\nReveal one of your PARTNER'S SECRETS in play. All consequences of the SECRET are resolved immediately.\n";
	}
	else if (whoChoose == 'R'||whoChoose=='N') {
		x = x + "Reaction\n";
	}
	
	if (explain_choices != "") {
		if (whoChoose == 'T' || whoChoose == 'C') {
			x = x + explain_choices+additionals.at(0).getFull()+"\n";
			//for (int j = 0; j < additionals.at(0).getCode().size(); j++) {

				//x = x + additionals.at(0).getCode().at(j) + ", ";
			//}
			x = x + "\n";
		}
		else {
			x = x + explain_choices + "\n";
		}
		
	}
	char alphabet[] = "ABCD";
	
	if (whoChoose == 'T' || whoChoose == 'C') {
		x = x + "If revealed\n";
	}
	if (whoChoose == 'T') {
		x = x + additionals.at(1).getFull() + "\n";
		//for (int j = 0; j < additionals.at(1).getCode().size(); j++) {

			//x = x + additionals.at(1).getCode().at(j) + ", ";
		//}
	}
	else if (whoChoose == 'C') {
		x = x + "Partner chooses\n";
	}

	for (int i = 0; i < choices.size(); i++) {
		if (whoChoose == 'B' || whoChoose == 'P'||whoChoose=='C'||whoChoose=='N') {
			x = x + alphabet[i] + " = " + choices.at(i).printFull();
		}
		else if (whoChoose == 'S'||whoChoose=='E'||whoChoose == 'R') {
			x = x + choices.at(i).printFull();
		}
		
	}
	if (whoChoose == 'B' || whoChoose == 'P') {
		if (additionals.size() > 0) {
			x = x + "ADDITIONAL EFFECTS\n";
		}
		for (int i = 0; i < additionals.size(); i++) {
			x = x + additionals.at(i).getFull() + "\n";
			//for (int j = 0; j < additionals.at(i).getCode().size(); j++) {

				//x = x + additionals.at(i).getCode().at(j) + ", ";
			//}
			//x = x + "\n";
		}
	}
	
	if (whoChoose == 'V' || whoChoose == 'R' || whoChoose == 'N') {
		x = x + "Minor Scene\nDoes not count towards CHAPTER LENGTH.\nYou may discard this SCENE face up at the beginning of your turn and draw a new one.\n";
	}

	x = x + "Deck: ";
	switch (deck) {
	case Sweet:
		x = x + "Sweet\n\n";
		break;
	case Serious:
		x = x + "Serious\n\n";
		break;
	case Drama:
		x = x + "Drama\n\n";
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
	x = x + text+"\n";

	//for (int i = 0; i < code.size(); i++) {
		//x = x + code.at(i)+", ";
	//}
	//if (code.size() > 0) {
		//x = x + "\n";
	//}
	return x;
};