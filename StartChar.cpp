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

	Session game{ x1, x2, traits1, traits2, occu1, occu2, features, fea1, fea2, per, plot, d1, d2, chapters, sweetS, seriousS, dramaS, hand1, hand2 };
	return game;
};

Session runGame(Session session) {
	
	std::string alphabet = "OABCD";
	int turn = 1;
	session = drawStarting(session);
	for (int j = 0; j < session.chapters.size(); j++) {
		std::cout << "\033[2J\033[1;1H";
		char choice1;
		char choice2;
		std::cout<<session.chapters.at(j).printFull();
		int temp1 = select(session.chapters.at(j).getChoices().size());
		choice1 = alphabet[temp1];
		int temp2 = select(session.chapters.at(j).getChoices().size());
		choice2= alphabet[temp2];
		
		
		for (int i = 0; i < session.chapters.at(j).getLength(); i++) {
			//std::cout << "\033[2J\033[1;1H";
			//int index = chooseScene(session, turn);
			Scene scene = session.sweetS.at(3);
			std::cout << scene.printFull();
			if (scene.getWho() == 'B') {

				temp1 = select(scene.getChoices().size());
				choice1 = alphabet[temp1];
				temp2 = select(scene.getChoices().size());
				choice2 = alphabet[temp2];
				session = resolveEffectsB(session, turn, scene, temp1, temp2);
				session = resolveAddi(session, turn, scene, temp1, temp2);
				//std::cout << session.hand1.at(5).printFull();
				
			}
			else {
				int temp = select(scene.getChoices().size());
				choice1 = alphabet[temp];
				session = resolveEffectsP(session, turn, scene, temp);
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

