#include "Enums.h"
#include "StartChar.h"
#include "ResolveEffects.h"
#include "RunGameHelper.h"
#include "BeforeScenes.h"
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




int startGame() {
	Session session = startSession();
	session = runGame(session);
	session = resolution(session);
	return 0;
};

Session startSession() {
	readyGame();
	Character x1 = startGender(1);
	Character x2 = startGender(2);
	std::vector<Trait> traits = importTraits("trait.txt");
	dealCards<std::vector<Trait>> t3 = startTraits(traits);
	traits = t3.deck;
	std::vector<Trait> trait1 = t3.p1;
	std::vector<Trait> trait2 = t3.p2;
	std::vector<Occupation> occus = importOccus("occupation.txt");
	dealCards<std::vector<Occupation>>o3 = startOccupation(occus);
	occus = o3.deck;
	Occupation occu1 = o3.p1.at(0);
	Occupation occu2 = o3.p2.at(0);
	std::vector<Feature> features = importFeatures("feature.txt");
	dealCards<std::vector<Feature>> f3 = startFeatures(features);
	features = f3.deck;
	std::vector<Feature> fea1 = f3.p1;
	std::vector<Feature> fea2 = f3.p2;
	
	//std::cout << features.at(features.size() - 1).printFull();
	//std::cout << features.at(features.size() - 2).printFull();
	PersonalityToken per = PersonalityToken();
	
	per.changeOccu(1, occu1);
	per.changeOccu(2, occu2);
	per.changeFeature(1, fea1.at(0));
	per.changeFeature(1, fea1.at(1));
	per.changeFeature(1, fea1.at(2));
	per.changeFeature(2, fea2.at(0));
	per.changeFeature(2, fea2.at(1));
	per.changeFeature(2, fea2.at(2));
	x1 = changeName(x1);
	x2 = changeName(x2);
	std::cout << "Now take a moment to introduce the characters you have created. Tell each other who your characters are in a few sentences.You should still not tell about how you met.\n";
	std::cout << "Press enter to start the game: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	Synopsis plot = selectSynopsis();
	//std::cout<< plot.printFull();
	std::vector<Destiny> d1 = plot.getDestinies();
	std::vector<Destiny> d2 = plot.getDestinies();
	std::vector<Chapter> chapters = importChapters("chapters.txt", "chapterEffect.txt");
	std::vector<Scene> sweetS = importScenes("scenesSweet.txt", "sceneEffectSweet.txt");
	
	std::vector<Scene> seriousS = importScenes("scenesSerious.txt", "sceneEffectSerious.txt");
	std::vector<Scene> dramaS = importScenes("scenesDrama.txt", "sceneEffectDrama.txt");
	
	std::vector<Scene> hand1;
	std::vector<Scene> hand2;
	std::vector<std::string> c;
	std::vector<Scene> secret1;
	std::vector<Scene> secret2;
	Session game{ x1, x2, traits, trait1, trait2, occus, occu1, occu2, features, fea1, fea2, per, plot, d1, d2, chapters, sweetS, seriousS, dramaS, hand1, hand2, c, secret1, secret2};
	return game;
};

Session runGame(Session session) {
	
	std::string alphabet = "OABCD";
	Scene scene = session.sweetS.at(0);
	int turn = 1;
	session = drawStarting(session);
	for (int j = 0; j < session.chapters.size(); j++) {
		std::cout << "\033[2J\033[1;1H";
		char choice1;
		char choice2;
		std::cout << session.chapters.at(j).printFull();
		std::cout << session.x1.getName() + ", make your choice for the chapter.\n";
		int temp1 = select(session.chapters.at(j).getChoices().size());
		choice1 = alphabet[temp1];
		std::cout << session.x2.getName() + ", make your choice for the chapter.\n";
		int temp2 = select(session.chapters.at(j).getChoices().size());
		choice2 = alphabet[temp2];
		session = resolveEffectsC(session, session.chapters.at(j), temp1, temp2);
		int behalf = 0;
		for (int i = 0; i < session.chapters.at(j).getLength(); i++) {
			std::cout << "\033[2J\033[1;1H";



			int doubleImpact = 0;
			int position = 0;
			if (std::find(session.carryOver.begin(), session.carryOver.end(), "DOUBLEIMPACT") != session.carryOver.end()) {
				position = std::find(session.carryOver.begin(), session.carryOver.end(), "DOUBLEIMPACT") - session.carryOver.begin();
				doubleImpact = std::stoi(session.carryOver.at(position + 1));
			}
			int doubleImpactB = 0;
			if (std::find(session.carryOver.begin(), session.carryOver.end(), "DOUBLEIMPACTB") != session.carryOver.end()) {
				position = std::find(session.carryOver.begin(), session.carryOver.end(), "DOUBLEIMPACTB") - session.carryOver.begin();
				doubleImpactB = 1;
			}
			if (std::find(session.carryOver.begin(), session.carryOver.end(), "DOUBLEIMPACTPT") != session.carryOver.end()) {
				position = std::find(session.carryOver.begin(), session.carryOver.end(), "DOUBLEIMPACTPT") - session.carryOver.begin();
				doubleImpactB = 2;
			}
			if (std::find(session.carryOver.begin(), session.carryOver.end(), "BEHALF") != session.carryOver.end()) {
				position = std::find(session.carryOver.begin(), session.carryOver.end(), "BEHALF") - session.carryOver.begin();
				behalf++;
			}
			int behalfCho = 0;
			if (std::find(session.carryOver.begin(), session.carryOver.end(), "BEHALFCHO") != session.carryOver.end()) {
				position = std::find(session.carryOver.begin(), session.carryOver.end(), "BEHALFCHO") - session.carryOver.begin();
				behalfCho = 1;
			}


			int index = 8;
			if (behalf != 0) {
				if (turn == 1) {
					std::cout << "Due to MASQUERADE, " + session.x2.getName()+" is playing this card on "+session.x1.getName()+"\'s behalf.\n";
					index = chooseScene(session, 1);
					
					
				}
				else {
					std::cout << "Due to MASQUERADE, " + session.x1.getName() + " is playing this card on " + session.x2.getName() + "\'s behalf.\n";
					index = chooseScene(session, 2);
					
				}
			}
			else {
				index = chooseScene(session, turn);
				if (turn == 1) {
					while (session.hand1.at(index).getWho() == 'R' || session.hand1.at(index).getWho() == 'N') {
						std::cout << session.x1.getName() + ", you have to discard the reaction as a minor scene.\n";
						session.hand1.erase(session.hand1.begin() + index);
						session = drawFill(session, session.chapters.at(j).getDraw().at(0));
						index = chooseScene(session, turn);
					}
					while ( session.hand1.at(index).getWho() == 'V') {
						std::cout << session.x1.getName() + ", do you want to discard this minor scene?\n1 = Yes\n2 = No\n";
						int temp = select(2);
						if (temp == 0) {
							session.hand1.erase(session.hand1.begin() + index);
							session = drawFill(session, session.chapters.at(j).getDraw().at(0));
							index = chooseScene(session, turn);
						}
						else {
							break;
						}
					}
					
				}
				else {
					while (session.hand2.at(index).getWho() == 'R' || session.hand2.at(index).getWho() == 'N') {
						std::cout << session.x2.getName() + ", you have to discard the reaction as a minor scene.\n";
						session.hand2.erase(session.hand2.begin() + index);
						session = drawFill(session, session.chapters.at(j).getDraw().at(0));
						index = chooseScene(session, turn);
					}
					while (session.hand2.at(index).getWho() == 'V') {
						std::cout << session.x2.getName() + ", do you want to discard this minor scene?\n1 = Yes\n2 = No\n";
						int temp = select(2);
						if (temp == 0) {
							session.hand2.erase(session.hand2.begin() + index);
							session = drawFill(session, session.chapters.at(j).getDraw().at(0));
							index = chooseScene(session, turn);
						}
						else {
							break;
						}
					}
					
				}
			}

			//get the current scene
			if (turn == 1) {
				scene = session.hand1.at(index);
				session.hand1.erase(session.hand1.begin() + index);
			}
			else {
				scene = session.hand2.at(index);
				session.hand2.erase(session.hand2.begin() + index);
			}

			//resolve effects before players' choices
			session = specialOp(session, scene.getIndex(), scene.getDeck(), turn, scene);
			if (turn == 1) {
				scene = session.hand1.at(session.hand1.size()-1);
				session.hand1.erase(session.hand1.begin() + session.hand1.size() - 1);
			}
			else {
				scene = session.hand2.at(session.hand2.size() - 1);
				session.hand2.erase(session.hand2.begin() + session.hand2.size() - 1);
			}

			

			if (scene.getWho() == 'B') {
				//check if a reaction at place 0 can be played
				session = reaction(session, scene, turn, 0);
				std::cout << session.x1.getName() + ", make your choice for the scene.\n";
				temp1 = select(scene.getChoices().size());
				choice1 = alphabet[temp1];
				session = reaction(session, scene, 1, 1);
				session = reaction(session, scene, 2, 4);
				if (std::find(session.carryOver.begin(), session.carryOver.end(), "R181") != session.carryOver.end()) {
					position = std::find(session.carryOver.begin(), session.carryOver.end(), "R181") - session.carryOver.begin();
					session.carryOver.erase(session.carryOver.begin() + session.carryOver.size() - 1);
					std::cout << session.x1.getName() + ", make your choice for the scene again.\n";
					temp1 = select(scene.getChoices().size());
					choice1 = alphabet[temp1];
				}
				std::cout << session.x2.getName() + ", make your choice for the scene.\n";
				temp2 = select(scene.getChoices().size());
				choice2 = alphabet[temp2];
				session = reaction(session, scene, 2, 1);
				session = reaction(session, scene, 1, 4);
				if (std::find(session.carryOver.begin(), session.carryOver.end(), "R182") != session.carryOver.end()) {
					position = std::find(session.carryOver.begin(), session.carryOver.end(), "R182") - session.carryOver.begin();
					session.carryOver.erase(session.carryOver.begin() + session.carryOver.size() - 1);
					std::cout << session.x2.getName() + ", make your choice for the scene again.\n";
					temp2 = select(scene.getChoices().size());
					choice2 = alphabet[temp2];
				}
				session = reaction(session, scene, 0, 3);
				if (temp2 != temp1) {
					session = reaction(session, scene, 0, 5);
				}
				int reaction = 1;
				int rsize = 10;
				while (session.carryOver.size()>0&&rsize>session.carryOver.size()) {
					rsize = session.carryOver.size();
					if (std::find(session.carryOver.begin(), session.carryOver.end(), "R19") != session.carryOver.end()) {
						//todo: only partner choose effect
						position = std::find(session.carryOver.begin(), session.carryOver.end(), "R19") - session.carryOver.begin();
						session.carryOver.erase(session.carryOver.begin() + position);
						if (turn == 1) {
							session = reactionEffect(session, scene, 19, turn, temp2);
						}
						else {
							session = reactionEffect(session, scene, 19, turn, temp1);
						}

						continue;
					}
					if (std::find(session.carryOver.begin(), session.carryOver.end(), "R28") != session.carryOver.end()) {
						position = std::find(session.carryOver.begin(), session.carryOver.end(), "R28") - session.carryOver.begin();
						session.carryOver.erase(session.carryOver.begin() + position);
						if (turn == 1) {
							session = reactionEffect(session, scene, 28, turn, temp2);
						}
						else {
							session = reactionEffect(session, scene, 28, turn, temp1);
						}
						continue;
					}
					if (std::find(session.carryOver.begin(), session.carryOver.end(), "R301") != session.carryOver.end() || std::find(session.carryOver.begin(), session.carryOver.end(), "R161") != session.carryOver.end()) {
						if (std::find(session.carryOver.begin(), session.carryOver.end(), "R301") != session.carryOver.end()) {
							position = std::find(session.carryOver.begin(), session.carryOver.end(), "R301") - session.carryOver.begin();
						}
						else {
							position = std::find(session.carryOver.begin(), session.carryOver.end(), "R161") - session.carryOver.begin();
						}
						session.carryOver.erase(session.carryOver.begin() + position);
						std::cout << session.x1.getName() + ", make your choice for the scene again.\n";
						temp1 = select(scene.getChoices().size());
						choice1 = alphabet[temp1];
					}else if (std::find(session.carryOver.begin(), session.carryOver.end(), "R302") != session.carryOver.end() || std::find(session.carryOver.begin(), session.carryOver.end(), "R162") != session.carryOver.end()) {
						if (std::find(session.carryOver.begin(), session.carryOver.end(), "R302") != session.carryOver.end()) {
							position = std::find(session.carryOver.begin(), session.carryOver.end(), "R302") - session.carryOver.begin();
						}
						else {
							position = std::find(session.carryOver.begin(), session.carryOver.end(), "R162") - session.carryOver.begin();
						}
						session.carryOver.erase(session.carryOver.begin() + session.carryOver.size() - 1);
						std::cout << session.x2.getName() + ", make your choice for the scene again.\n";
						temp2 = select(scene.getChoices().size());
						choice2 = alphabet[temp2];
					}
					if (std::find(session.carryOver.begin(), session.carryOver.end(), "RS301") != session.carryOver.end()) {
						position = std::find(session.carryOver.begin(), session.carryOver.end(), "RS301") - session.carryOver.begin();
						session.carryOver.erase(session.carryOver.begin() + position);
						temp2 = temp1;
						session = drawFill(session, session.chapters.at(j).getDraw().at(0));
					}
					else if (std::find(session.carryOver.begin(), session.carryOver.end(), "RS302") != session.carryOver.end()) {
						position = std::find(session.carryOver.begin(), session.carryOver.end(), "RS302") - session.carryOver.begin();
						session.carryOver.erase(session.carryOver.begin() + position);
						temp1 = temp2;
						session = drawFill(session, session.chapters.at(j).getDraw().at(0));
					}
				}

				//todo: situation #6 DECIDEFIRST partner chooses first
				if (behalfCho != 0) {
					session = resolveEffectsB(session, turn, scene, temp2, temp1);
					session = resolveAddi(session, turn, scene, temp2, temp1);
				}
				else if (behalf != 0) {
					if (turn == 1) {
						session = resolveEffectsB(session, 2, scene, temp1, temp2);
						session = resolveAddi(session, 2, scene, temp1, temp2);
					}
					else {
						session = resolveEffectsB(session, 1, scene, temp1, temp2);
						session = resolveAddi(session, 1, scene, temp1, temp2);
					}
					
				}
				else {
					session = resolveEffectsB(session, turn, scene, temp1, temp2);
					session = resolveAddi(session, turn, scene, temp1, temp2);
				}

				//std::cout << session.hand1.at(5).printFull();
				if (doubleImpact != 0) {
					position = std::find(session.carryOver.begin(), session.carryOver.end(), "DOUBLEIMPACT") - session.carryOver.begin();
					session.carryOver.erase(session.carryOver.begin() + position, session.carryOver.begin() + position + 2);
				}
				if (doubleImpactB != 0) {
					if (std::find(session.carryOver.begin(), session.carryOver.end(), "DOUBLEIMPACTPT") != session.carryOver.end()) {
						position = std::find(session.carryOver.begin(), session.carryOver.end(), "DOUBLEIMPACTPT") - session.carryOver.begin();
					}
					else {
						position = std::find(session.carryOver.begin(), session.carryOver.end(), "DOUBLEIMPACTB") - session.carryOver.begin();
					}
					session.carryOver.erase(session.carryOver.begin() + position);
				}
				if (behalf == 2) {
					position = std::find(session.carryOver.begin(), session.carryOver.end(), "BEHALF") - session.carryOver.begin();
					session.carryOver.erase(session.carryOver.begin() + position);
					std::cout << "MASQUERADE effect has ended.\n";
					behalf = 0;
				}
				if (behalfCho != 0) {
					position = std::find(session.carryOver.begin(), session.carryOver.end(), "BEHALFCHO") - session.carryOver.begin();
					session.carryOver.erase(session.carryOver.begin() + position);
				}
				
			}
			else if (scene.getWho() == 'P') {
				session = reaction(session, scene, turn, 2);
				if (session.carryOver.size() > 0) {
					if (std::find(session.carryOver.begin(), session.carryOver.end(), "R29") != session.carryOver.end()) {
						position = std::find(session.carryOver.begin(), session.carryOver.end(), "R29") - session.carryOver.begin();
						session.carryOver.erase(session.carryOver.begin() + position);
						if (turn == 1) {
							session = reactionEffect(session, scene, 29, turn, temp2);
						}
						else {
							session = reactionEffect(session, scene, 29, turn, temp1);
						}
						continue;
					}
				}
				if (behalfCho != 0 || behalf != 0) {
					if (turn == 1) {
						std::cout << session.x1.getName() + ", make your choice for the scene.\n";
					}
					else {
						std::cout << session.x2.getName() + ", make your choice for the scene.\n";
					}

				}
				else {
					if (turn == 1) {
						std::cout << session.x2.getName() + ", make your choice for the scene.\n";
					}
					else {
						std::cout << session.x1.getName() + ", make your choice for the scene.\n";
					}
				}
				
				int temp = select(scene.getChoices().size());
				choice1 = alphabet[temp];
				session = reaction(session, scene, turn, 1);
				if (turn == 1) {
					session = reaction(session, scene, 2, 4);
				}
				else {
					session = reaction(session, scene, 1, 4);
				}
				session = reaction(session, scene, turn, 3);
				int rsize = 10;
				while (session.carryOver.size() > 0&&rsize>session.carryOver.size()) {
					
					rsize = session.carryOver.size();
					if (std::find(session.carryOver.begin(), session.carryOver.end(), "R28") != session.carryOver.end()) {
						position = std::find(session.carryOver.begin(), session.carryOver.end(), "R28") - session.carryOver.begin();
						session.carryOver.erase(session.carryOver.begin() + session.carryOver.size() - 1);
						if (turn == 1) {
							session = reactionEffect(session, scene, 28, turn, temp);
						}
						else {
							session = reactionEffect(session, scene, 28, turn, temp);
						}
						continue;
					}
					if (std::find(session.carryOver.begin(), session.carryOver.end(), "R301") != session.carryOver.end() || std::find(session.carryOver.begin(), session.carryOver.end(), "R181") != session.carryOver.end()) {
						if (std::find(session.carryOver.begin(), session.carryOver.end(), "R181") != session.carryOver.end()) {
							session = reactionEffect(session, scene, 18, 2, temp);
							position = std::find(session.carryOver.begin(), session.carryOver.end(), "R181") - session.carryOver.begin();
						}
						else {
							position = std::find(session.carryOver.begin(), session.carryOver.end(), "R301") - session.carryOver.begin();
						}
						
						session.carryOver.erase(session.carryOver.begin() + position);
						std::cout << session.x1.getName() + ", make your choice for the scene again.\n";
						temp = select(scene.getChoices().size());
						choice1 = alphabet[temp];
						
					}
					else if (std::find(session.carryOver.begin(), session.carryOver.end(), "R302") != session.carryOver.end() || std::find(session.carryOver.begin(), session.carryOver.end(), "R182") != session.carryOver.end()) {
						if (std::find(session.carryOver.begin(), session.carryOver.end(), "R182") != session.carryOver.end()) {
							session = reactionEffect(session, scene, 18, 1, temp);
							position = std::find(session.carryOver.begin(), session.carryOver.end(), "R182") - session.carryOver.begin();
						}
						else {
							position = std::find(session.carryOver.begin(), session.carryOver.end(), "R302") - session.carryOver.begin();
						}
						session.carryOver.erase(session.carryOver.begin() + position);
						std::cout << session.x2.getName() + ", make your choice for the scene again.\n";
						temp = select(scene.getChoices().size());
						choice1 = alphabet[temp];
					}
				}
				if (behalfCho != 0||behalf!=0) {
					if (turn == 1) {
						session = resolveEffectsP(session, 2, scene, temp);
					}
					else {
						session = resolveEffectsP(session, 1, scene, temp);
					}

				}
				else {

					session = resolveEffectsP(session, turn, scene, temp);
				}

				if (doubleImpact != 0) {
					position = std::find(session.carryOver.begin(), session.carryOver.end(), "DOUBLEIMPACT") - session.carryOver.begin();
					session.carryOver.erase(session.carryOver.begin() + position, session.carryOver.begin() + position + 2);
				}
				if (doubleImpactB != 0) {
					position = std::find(session.carryOver.begin(), session.carryOver.end(), "DOUBLEIMPACTB") - session.carryOver.begin();
					session.carryOver.erase(session.carryOver.begin() + position);
				}
				if (behalf == 2) {
					position = std::find(session.carryOver.begin(), session.carryOver.end(), "BEHALF") - session.carryOver.begin();
					std::cout << "MASQUERADE effect has ended.\n";
					session.carryOver.erase(session.carryOver.begin() + position);
					behalf = 0;
				}
				if (behalfCho != 0) {
					position = std::find(session.carryOver.begin(), session.carryOver.end(), "BEHALFCHO") - session.carryOver.begin();
					session.carryOver.erase(session.carryOver.begin() + position);
				}
				//check if secrets are revealed
				if (session.carryOver.size()>0&&std::find(session.carryOver.begin(), session.carryOver.end(), "RS") != session.carryOver.end() || std::find(session.carryOver.begin(), session.carryOver.end(), "RSS") != session.carryOver.end() || std::find(session.carryOver.begin(), session.carryOver.end(), "RSALL") != session.carryOver.end()) {
					if (std::find(session.carryOver.begin(), session.carryOver.end(), "RS") != session.carryOver.end()) {
						position = std::find(session.carryOver.begin(), session.carryOver.end(), "RS") - session.carryOver.begin();
					}
					else if (std::find(session.carryOver.begin(), session.carryOver.end(), "RSS") != session.carryOver.end()) {
						position = std::find(session.carryOver.begin(), session.carryOver.end(), "RSS") - session.carryOver.begin();
					}
					else {
						position = std::find(session.carryOver.begin(), session.carryOver.end(), "RSALL") - session.carryOver.begin();
					}

					int index = std::stoi(session.carryOver.at(position + 1));
					i = i + index;
					for (int k = 0; k < index; k++) {
						switch (index)
						{
						case 1:
							if (turn == 1 || session.carryOver.at(0) == "RSS" && session.secret1.size() > 0) {
								scene = session.secret1.at(0);
								session.secret1.erase(session.secret1.begin());
							}
							else {
								scene = session.secret2.at(0);
								session.secret2.erase(session.secret2.begin());
							}
							break;
						default:
							if (session.secret1.size() > 0) {
								scene = session.secret1.at(0);
								session.secret1.erase(session.secret1.begin());
							}
							else if (session.secret2.size() > 0) {
								scene = session.secret2.at(0);
								session.secret2.erase(session.secret2.begin());
							}
							break;
						}


						std::cout << scene.printFull();
						if (scene.getWho() == 'C') {
							int temp = select(scene.getChoices().size());
							choice1 = alphabet[temp];
							session = resolveEffectsP(session, turn, scene, temp);
						}
						else if (scene.getWho() == 'T') {
							session = resolveChoice(session, turn, turn, scene.getAddis().at(1).getCode());
						}

					}
					session.carryOver.erase(session.carryOver.begin(), session.carryOver.begin() + 2);

				}
			}
			else if (scene.getWho() == 'S') {
				if (scene.getIndex() == 19) {
					session = resolveChoice(session, turn, turn, scene.getChoices().at(0).getCode());
				}
				else {
					session = resolveEffectsP(session, turn, scene, 0);
				}

			}
			else if (scene.getWho() == 'E') {
				session = SEEffect(session, scene, turn);
			}
			else if (scene.getWho() == 'T' || scene.getWho() == 'C') {
				if (turn == 1) {
					session.secret1.push_back(scene);
					std::cout << "This secret is NOT revealed to " + session.x2.getName() + ".\n";
				}
				else {
					session.secret2.push_back(scene);
					std::cout << "This secret is NOT revealed to " + session.x1.getName() + ".\n";
				}
			}
			else if (scene.getWho() == 'V') {
				std::cout << scene.printFull();
				if (turn == 1 && session.secret2.size() > 0) {
					scene = session.secret2.at(0);
					std::cout << scene.printFull();
					if (scene.getWho() == 'C') {
						int temp = select(scene.getChoices().size());
						choice1 = alphabet[temp];
						session = resolveEffectsP(session, turn, scene, temp);
					}
					else if (scene.getWho() == 'T') {
						session = resolveChoice(session, turn, turn, scene.getAddis().at(1).getCode());
					}
					session.secret2.erase(session.secret2.begin());
					i--;
				}
				else if (turn == 2 && session.secret1.size() > 0) {
					scene = session.secret1.at(0);
					std::cout << scene.printFull();
					if (scene.getWho() == 'C') {
						int temp = select(scene.getChoices().size());
						choice1 = alphabet[temp];
						session = resolveEffectsP(session, turn, scene, temp);
					}
					else if (scene.getWho() == 'T') {
						session = resolveChoice(session, turn, turn, scene.getAddis().at(1).getCode());
					}
					session.secret1.erase(session.secret1.begin());
					i--;
				}
			}

			std::cout << "All effects are resolved for this scene. \n1 = Start the next scene.\n2 = View the current game board.\n";
			int next = select(2);
			if (next == 1) {
				seeBoard(session, turn);
			}

			if (turn == 1) {
				turn = 2;
			}
			else {
				turn = 1;
			}
			
			session = drawFill(session, session.chapters.at(j).getDraw().at(0));
		}


	}
	return session;
};



Session resolution(Session session) {
	std::cout << "\033[2J\033[1;1H";
	std::cout << "COMPATIBLE?\n";
	std::cout << "You've made up your mind about what you want, but are you happy with how things are going with your partner?\n";
	std::cout << "BOTH select final DESTINY.\n";
	session = chooseDestiny(session);
	std::cout << "\033[2J\033[1;1H";
	std::cout << "RESOLUTION\n";
	std::cout << "1. Reveal your DESTINIES. Your DESTINIES determine how it all ends.\n";
	std::cout << session.x1.getName()+" has chosen "+session.d1.at(findDestiny(session, 1)).getName()+"\n";
	std::cout << session.x2.getName() + " has chosen " + session.d2.at(findDestiny(session, 2)).getName()+"\n";
	std::cout << "2. If you have any SECRETS in play, you now reveal and resolve them as if unrevealed. You alternate in revealing your SECRETS, each choosing one at random to reveal and resolve, until all have been revealed.\n";
	session = unrevealedSecrets(session);
	std::cout << "3. Reveal your TRAITS and check if you have realized your TRAIT GOALS.\n";
	std::cout << " - Each achieved TRAIT GOAL is +3 to you.\n";
	std::cout << " - Each missed TRAIT GOAL is -1 to you.\n";
	session = traitGoals(session);
	std::cout << "\n" + session.x1.getName() + "\'s satisfaction: " + std::to_string(session.x1.getSatisfaction()) + "\n";
	std::cout << session.x2.getName() + "\'s satisfaction: " + std::to_string(session.x2.getSatisfaction()) + "\n\n";
	std::cout << "4. Now you can see if you have fulfilled your characters\' DESTINIES.\n";
	if (fullfilDestiny(session, 1, findDestiny(session, 1), findDestiny(session,2)) == 1) {
		std::cout << session.x1.getName() + " has fulfilled the DESTINY: " + session.d1.at(findDestiny(session, 1)).getName() + ". Congrats!\n";
	}
	else {
		std::cout << session.x1.getName() + " did not fulfilled the DESTINY: " + session.d1.at(findDestiny(session, 1)).getName() + "\n";
	}
	if (fullfilDestiny(session, 2, findDestiny(session, 1), findDestiny(session, 2)) == 1) {
		std::cout << session.x2.getName() + " has fulfilled the DESTINY: " + session.d2.at(findDestiny(session, 2)).getName() + ". Congrats!\n";
	}
	else {
		std::cout << session.x2.getName() + " did not fulfilled the DESTINY: " + session.d2.at(findDestiny(session, 2)).getName() + "\n";
	}
	std::cout << "Remember. Fulfilling a destiny isn\'t everything. The story is.\n\n";
	std::cout << "Thank you for playing the game :)\n";
	return session;
};

