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
	std::vector<Trait> traits1 = startTraits(1);
	std::vector<Trait> traits2 = startTraits(2);
	std::vector<Occupation> occus = importOccus("occupation.txt");
	dealCards<std::vector<Occupation>>o3 = startOccupation(occus);
	occus = o3.deck;
	Occupation occu1 = o3.p1.at(0);
	Occupation occu2 = o3.p1.at(0);
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
	Session game{ x1, x2, traits1, traits2, occus, occu1, occu2, features, fea1, fea2, per, plot, d1, d2, chapters, sweetS, seriousS, dramaS, hand1, hand2, c, secret1, secret2};
	//game = ApplyEffect(game, 1, game.occu1.getDim(), game.occu1.getNum());
	//game = ApplyEffect(game, 2, game.occu2.getDim(), game.occu2.getNum());
	return game;
};

Session runGame(Session session) {
	
	std::string alphabet = "OABCD";
	int turn = 1;
	session = drawStarting(session);
	for (int j = 0; j <1; j++) {
		std::cout << "\033[2J\033[1;1H";
		char choice1;
		char choice2;
		std::cout<<session.chapters.at(j).printFull();
		std::cout << session.x1.getName()+", make your choice for the chapter.\n";
		int temp1 = select(session.chapters.at(j).getChoices().size());
		choice1 = alphabet[temp1];
		std::cout << session.x2.getName() + ", make your choice for the chapter.\n";
		int temp2 = select(session.chapters.at(j).getChoices().size());
		choice2= alphabet[temp2];
		session = resolveEffectsC(session,session.chapters.at(j), temp1, temp2);
		session.secret1.push_back(session.dramaS.at(12));
		session.secret1.push_back(session.seriousS.at(26));
		session.secret2.push_back(session.sweetS.at(28));
		int behalf = 0;
		for (int i = 0; i < session.chapters.at(j).getLength(); i++) {
			//std::cout << "\033[2J\033[1;1H";
			
			

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
				behalf ++;
			}
			int behalfCho = 0;
			if (std::find(session.carryOver.begin(), session.carryOver.end(), "BEHALFCHO") != session.carryOver.end()) {
				position = std::find(session.carryOver.begin(), session.carryOver.end(), "BEHALFCHO") - session.carryOver.begin();
				behalfCho = 1;
			}
			

			int index = 8;
			if (behalf != 0) {
				if (turn == 1) {
					//index = chooseScene(session, 2);
				}
				else {
					//index = chooseScene(session, 1);
				}
			}
			else {
				//index = chooseScene(session, turn);
			}
			
			Scene scene = session.hand1.at(0);

			session = specialOp(session, scene.getIndex(), scene.getDeck(), turn, scene);

			if (scene.getWho() == 'B') {
				std::cout << session.x1.getName() + ", make your choice for the scene.\n";
				temp1 = select(scene.getChoices().size());
				choice1 = alphabet[temp1];
				std::cout << session.x2.getName() + ", make your choice for the scene.\n";
				temp2 = select(scene.getChoices().size());
				choice2 = alphabet[temp2];
				if (behalfCho != 0) {
					session = resolveEffectsB(session, turn, scene, temp2, temp1);
					session = resolveAddi(session, turn, scene, temp2, temp1);
				}
				else {
					session = resolveEffectsB(session, turn, scene, temp1, temp2);
					session = resolveAddi(session, turn, scene, temp1, temp2);
				}
				
				//std::cout << session.hand1.at(5).printFull();
				if (doubleImpact != 0) {
					session.carryOver.erase(session.carryOver.begin() + position, session.carryOver.begin() + position + 2);
				}
				if (doubleImpactB != 0) {
					session.carryOver.erase(session.carryOver.begin() + position);
				}
				if (behalf == 2) {
					session.carryOver.erase(session.carryOver.begin() + position);
				}
				if (behalfCho != 0) {
					session.carryOver.erase(session.carryOver.begin() + position);
				}
			}
			else if(scene.getWho()=='P') {
				int temp = select(scene.getChoices().size());
				choice1 = alphabet[temp];
				if (behalfCho != 0) {
					if (turn == 1) {
						std::cout << session.x2.getName() + ", make your choice for the scene.\n";
						session = resolveEffectsP(session, 2, scene, temp);
					}
					else {
						std::cout << session.x1.getName() + ", make your choice for the scene.\n";
						session = resolveEffectsP(session, 1, scene, temp);
					}
					
				}
				else {
					session = resolveEffectsP(session, turn, scene, temp);
				}
				
				if (doubleImpact != 0) {
					session.carryOver.erase(session.carryOver.begin() + position, session.carryOver.begin() + position + 2);
				}
				if (doubleImpactB != 0) {
					session.carryOver.erase(session.carryOver.begin() + position);
				}
				if (behalf == 2) {
					session.carryOver.erase(session.carryOver.begin() + position);
				}
				if (behalfCho != 0) {
					session.carryOver.erase(session.carryOver.begin() + position);
				}
				//check if secrets are revealed
				if (std::find(session.carryOver.begin(), session.carryOver.end(), "RS") != session.carryOver.end()|| std::find(session.carryOver.begin(), session.carryOver.end(), "RSS") != session.carryOver.end()|| std::find(session.carryOver.begin(), session.carryOver.end(), "RSALL") != session.carryOver.end()) {
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
							if (turn == 1||session.carryOver.at(0)=="RSS"&&session.secret1.size()>0) {
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
				session = resolveEffectsB(session, turn, scene, 0, 0);
				if (scene.getIndex() == 34) {
					session = resolveEffectsB(session, turn, scene, 1, 1);
				}
			}
			else if (scene.getWho() == 'E') {
				session = SEEffect(session, scene, turn);
			}
			else if (scene.getWho() == 'T' || scene.getWho() == 'C') {
				if (turn == 1) {
					session.secret1.push_back(scene);
				}
				else {
					session.secret2.push_back(scene);
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

			if (turn == 1) {
				turn = 2;
			}
			else {
				turn = 1;
			}
			std::cout << std::to_string(session.x1.getSatisfaction());
			std::cout << std::to_string(session.x2.getSatisfaction());
			session = drawFill(session, session.chapters.at(j).getDraw().at(0));
		}
	}
	
	
	return session;
};



Session resolution(Session session) {
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
