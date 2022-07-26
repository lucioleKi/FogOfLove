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

	Session game{ x1, x2, traits1, traits2, occus, occu1, occu2, features, fea1, fea2, per, plot, d1, d2, chapters, sweetS, seriousS, dramaS, hand1, hand2 };
	//game = ApplyEffect(game, 1, game.occu1.getDim(), game.occu1.getNum());
	//game = ApplyEffect(game, 2, game.occu2.getDim(), game.occu2.getNum());
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
		session = resolveEffectsC(session,session.chapters.at(j), temp1, temp2);
		
		for (int i = 0; i < session.chapters.at(j).getLength(); i++) {
			//std::cout << "\033[2J\033[1;1H";
			//int index = chooseScene(session, turn);
			Scene scene = session.sweetS.at(26);
			
			session = specialOp(session, scene.getIndex(), scene.getDeck(), turn, scene);
			
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

Session specialOp(Session session, int index, Deck deck, int turn, Scene scene) {
	if (index == 26 && deck == Sweet) {
		if (turn == 1) {
			session.per.change(1, 4, 1);
			scene.setLine(scene.getLine()+"\nPLAYER Extroversion + 1.");
			std::cout << scene.printFull();
			session.hand1.push_back(scene);
		}
		else {
			session.per.change(2, 4, 1);
			scene.setLine(scene.getLine() + "\nPLAYER Extroversion + 1.");
			std::cout << scene.printFull();
			session.hand2.push_back(scene);
		}
		return session;
	}
	else if (index == 12 && deck == Drama) {
		if (turn == 1) {
			session.per.change(1, 6, 1);
			scene.setLine(scene.getLine() + "\nPLAYER discard up to 2 scenes. Sensitivity + 1.");
			std::cout << scene.printFull();
			std::cout << "Discard the first scene. If you do not wish to discard, choose the last option.\n";
			for (int i = 0; i < session.hand1.size(); i++) {
				std::cout << std::to_string(i+1)+" = " + session.hand1.at(i).getTitle() +"\n";
			}
			std::cout << std::to_string(session.hand1.size() + 1)+" = Discard no scene.\n";
			int temp = select(session.hand1.size()+1);
			if (temp == session.hand1.size()) {
				session.hand1.push_back(scene);
				return session;
			}
			else {
				session.hand1.erase(session.hand1.begin() + temp);
			}
			std::cout << "Discard the second scene. If you do not wish to discard, choose the last option.\n";
			for (int i = 0; i < session.hand1.size(); i++) {
				std::cout << std::to_string(i + 1) + " = " + session.hand1.at(i).getTitle() + "\n";
			}
			std::cout << std::to_string(session.hand1.size() + 1) + " = Discard no scene.\n";
			temp = select(session.hand1.size() + 1);
			if (temp == session.hand1.size()) {
				session.hand1.push_back(scene);
				return session;
			}
			else {
				session.hand1.erase(session.hand1.begin() + temp);
			}
			session.hand1.push_back(scene);
			return session;
		}
		else {
			session.per.change(2, 6, 1);
			scene.setLine(scene.getLine() + "\nPLAYER discard up to 2 scenes. Sensitivity + 1.");
			std::cout << scene.printFull();
			std::cout << "Discard the first scene. If you do not wish to discard, choose the last option.\n";
			for (int i = 0; i < session.hand2.size(); i++) {
				std::cout << std::to_string(i + 1) + " = " + session.hand2.at(i).getTitle() + "\n";
			}
			std::cout << std::to_string(session.hand2.size() + 1) + " = Discard no scene.\n";
			int temp = select(session.hand2.size() + 1);
			if (temp == session.hand2.size()) {
				session.hand2.push_back(scene);
				return session;
			}
			else {
				session.hand2.erase(session.hand2.begin() + temp);
			}
			std::cout << "Discard the second scene. If you do not wish to discard, choose the last option.\n";
			for (int i = 0; i < session.hand2.size(); i++) {
				std::cout << std::to_string(i + 1) + " = " + session.hand2.at(i).getTitle() + "\n";
			}
			std::cout << std::to_string(session.hand2.size() + 1) + " = Discard no scene.\n";
			temp = select(session.hand2.size() + 1);
			if (temp == session.hand2.size()) {
				session.hand2.push_back(scene);
				return session;
			}
			else {
				session.hand2.erase(session.hand2.begin() + temp);
			}
			session.hand2.push_back(scene);
			return session;
		}
		return session;
	}

	else if (index==13&&deck==Drama|| index == 10 && deck == Drama) {
		if (turn == 1) {
			session.per.change(1, 6, 1);
			scene.setLine(scene.getLine() + "\nPLAYER may discard any number of SCENES.");
			std::cout << scene.printFull();
			while (session.hand1.size() > 0) {
				std::cout << "Discard a scene. If you do not wish to discard, choose the last option.\n";
				for (int i = 0; i < session.hand1.size(); i++) {
					std::cout << std::to_string(i + 1) + " = " + session.hand1.at(i).getTitle() + "\n";
				}
				std::cout << std::to_string(session.hand1.size() + 1) + " = Discard no scene.\n";
				int temp = select(session.hand1.size() + 1);
				if (temp == session.hand1.size()) {
					session.hand1.push_back(scene);
					return session;
				}
				else {
					session.hand1.erase(session.hand1.begin() + temp);
				}
			}
			session.hand1.push_back(scene);
			return session;
		}
		else {
			session.per.change(2, 6, 1);
			scene.setLine(scene.getLine() + "\nPLAYER may discard any number of SCENES.");
			std::cout << scene.printFull();
			while (session.hand2.size() > 0) {
				std::cout << "Discard a scene. If you do not wish to discard, choose the last option.\n";
				for (int i = 0; i < session.hand2.size(); i++) {
					std::cout << std::to_string(i + 1) + " = " + session.hand2.at(i).getTitle() + "\n";
				}
				std::cout << std::to_string(session.hand1.size() + 1) + " = Discard no scene.\n";
				int temp = select(session.hand2.size() + 1);
				if (temp == session.hand2.size()) {
					session.hand2.push_back(scene);
					return session;
				}
				else {
					session.hand2.erase(session.hand2.begin() + temp);
				}
			}
			
			session.hand2.push_back(scene);
			return session;
		}
	}
	else if (index == 19 && deck == Serious) {
		if (turn == 1) {
			session.per.change(1, 0, 1);
			scene.setLine(scene.getLine() + "\nPLAYER discard a SCENE | Discipline + 1.");
			std::cout << scene.printFull();
			std::cout << "Discard a scene:\n";
			for (int i = 0; i < session.hand1.size(); i++) {
				std::cout << std::to_string(i + 1) + " = " + session.hand1.at(i).getTitle() + "\n";
			}
			int temp = select(session.hand1.size());
			session.hand1.erase(session.hand1.begin() + temp);
			session.hand1.push_back(scene);
		}
		else {
			session.per.change(2, 0, 1);
			scene.setLine(scene.getLine() + "\nPLAYER discard a SCENE | Discipline + 1.");
			std::cout << scene.printFull();
			std::cout << "Discard a scene:\n";
			for (int i = 0; i < session.hand2.size(); i++) {
				std::cout << std::to_string(i + 1) + " = " + session.hand2.at(i).getTitle() + "\n";
			}
			int temp = select(session.hand2.size());
			session.hand2.erase(session.hand2.begin() + temp);
			session.hand2.push_back(scene);
		}

		return session;
	}
	else {
		if (turn == 1) {
			std::cout << scene.printFull();
			session.hand1.push_back(scene);
		}
		else {
			std::cout << scene.printFull();
			session.hand2.push_back(scene);
		}
		
	}
	
	return session;
};

Session resolution(Session session) {
	std::cout << "COMPATIBLE?\n";
	std::cout << "You've made up your mind about what you want, but are you happy with how things are going with your partner?\n";
	std::cout << "BOTH select final DESTINY.\n";
	int d1 = chooseDestiny(session, 1);
	int d2 = chooseDestiny(session, 2);
	std::cout << "\033[2J\033[1;1H";
	std::cout << "RESOLUTION\n";
	std::cout << "1. Reveal your DESTINIES. Your DESTINIES determine how it all ends.\n";
	std::cout << session.x1.getName()+" has chosen "+session.d1.at(d1).getName();
	std::cout << session.x2.getName() + " has chosen " + session.d2.at(d2).getName();
	std::cout << "2. If you have any SECRETS in play, you now reveal and resolve them as if unrevealed. You alternate in revealing your SECRETS, each choosing one at random to reveal and resolve, until all have been revealed.\n";
	std::cout << "3. Reveal your TRAITS and check if you have realized your TRAIT GOALS.\n";
	std::cout << " - Each achieved TRAIT GOAL is +3 to you.\n";
	std::cout << " - Each missed TRAIT GOAL is -1 to you.\n";
	std::cout << "4. Now you can see if you have fulfilled your characters\' DESTINIES.\n";
	std::cout << "Remember. Fulfilling a destiny isn\'t everything. The story is.\n";
	return session;
};
