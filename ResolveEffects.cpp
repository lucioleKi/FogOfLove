#include "ResolveEffects.h"
#include "Enums.h"
#include "Scene.h"
#include "Session.h"
#include "VocabTranslator.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

Session resolveEffectsC(Session session, Chapter chapter, int choice1, int choice2) {
	Choice c1 = chapter.getChoices().at(choice1);
	Choice c2 = chapter.getChoices().at(choice2);
	if (c1.getCode().size() ==3 ) {
		int index = 0;
		std::vector<int> hand;
		for (int i = 0; i < session.d1.size(); i++) {
			if (session.d1.at(i).getIn()) {
				std::cout << session.d1.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}
		std::cout << "Select a DESTINY to discard:\n";
		int temp = select(index);
		session.d1.at(hand.at(temp)).changeIn();
	}
	else if (c1.getCode().size() == 4) {
		int index = 0;
		std::vector<int> hand;
		for (int i = 0; i < session.d1.size(); i++) {
			if (session.d1.at(i).getIn()&&session.d1.at(i).getName()!=c1.getCode().at(3)) {
				std::cout << session.d1.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}
		std::cout << "Select a DESTINY to discard:\n";
		int temp = select(index);
		session.d1.at(hand.at(temp)).changeIn();
	}
	if (c2.getCode().size() ==3) {
		int index = 0;
		std::vector<int> hand;
		for (int i = 0; i < session.d2.size(); i++) {
			if (session.d2.at(i).getIn()) {
				std::cout << session.d2.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}
		std::cout << "Select a DESTINY to discard:\n";
		int temp = select(index);
		session.d2.at(hand.at(temp)).changeIn();
	}
	else if (c2.getCode().size() == 4) {
		int index = 0;
		std::vector<int> hand;
		for (int i = 0; i < session.d2.size(); i++) {
			if (session.d2.at(i).getIn() && session.d2.at(i).getName() != c2.getCode().at(3)) {
				std::cout << session.d2.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}
		std::cout << "Select a DESTINY to discard:\n";
		int temp = select(index);
		session.d2.at(hand.at(temp)).changeIn();
	}

	int additionalMatch = -1;
	std::vector<std::string> matches = match2(choice1, choice2, 1);
	for (int i = 0; i < chapter.getAddis().size(); i++) {
		std::string c = chapter.getAddis().at(i).getCode().at(0);

		if (std::find(matches.begin(), matches.end(), c) != matches.end()) {
			//std::cout << c;
			additionalMatch = i;
		}
	}
	if (additionalMatch == -1) { return session; };
	std::vector<std::string> effects = chapter.getAddis().at(additionalMatch).getCode();
	std::cout << effects.at(0)+"\n";
	session.x1.setSatisfaction(std::stoi(effects.at(2)));
	session.x2.setSatisfaction(std::stoi(effects.at(2)));
	return session;
};

Session resolveEffectsB(Session game, int turn, Scene scene, int choice1, int choice2) {
	int player = turn;
	int other;
	if (player == 1) {
		int other = 2;
	}
	else {
		int other = 1;
	}

	//resolve PT effects
	Choice c1 = scene.getChoices().at(choice1);
	Choice c2 = scene.getChoices().at(choice2);
	for (int i = 0; i < c1.getDims().size(); i++) {
		if (c1.getNums().at(i) > 0) {
			game.per.change(1, c1.getDims().at(i)*2, c1.getNums().at(i));

		}
		else {
			game.per.change(1, c1.getDims().at(i)*2+1, (c1.getNums().at(i))*(-1));
		}
	}
	for (int i = 0; i < c2.getDims().size(); i++) {
		if (c2.getNums().at(i) > 0) {
			game.per.change(2, c2.getDims().at(i) * 2, c2.getNums().at(i));
		}
		else {
			game.per.change(2, c2.getDims().at(i) * 2 + 1, (c2.getNums().at(i))*(-1));
		}
	}
	//resolve satisfaction
	if (c1.getCode().size() > 0) {
		game = resolveChoice(game, 1, turn, c1.getCode());
	}
	if (c2.getCode().size() > 0) {
		game = resolveChoice(game, 2, turn, c2.getCode());
	}
	
	
	std::cout << game.per.printFull();
	std::cout << std::to_string(game.x1.getSatisfaction());
	std::cout << std::to_string(game.x2.getSatisfaction());
	return game;
};

Session resolveEffectsP(Session game, int turn, Scene scene, int choice1) {
	
	int player = turn;
	int other = 1;
	if (player == 1) {
		other = 2;
	}
	else {
		other = 1;
	}
	
	//resolve PT effects
	Choice c1 = scene.getChoices().at(choice1);
	
	

	for (int i = 0; i < c1.getDims().size(); i++) {
		if (c1.getNums().at(i) > 0) {
			game.per.change(1, c1.getDims().at(i) * 2, c1.getNums().at(i));
		}
		else {
			game.per.change(1, c1.getDims().at(i) * 2 + 1, c1.getNums().at(i));
		}
	}
	//std::cout << game.per.printFull();
	//resolve satisfaction
	game = resolveChoice(game, other, turn, c1.getCode());
	//std::cout << std::to_string(game.x1.getSatisfaction());
	//std::cout << std::to_string(game.x2.getSatisfaction());
	return game;
};

Session resolveChoice(Session game, int chooser, int player, std::vector<std::string> code) {
	//std::vector<std::string> code = c.getCode();
	int index = 0;
	if (code.size() > 0 && code.at(0) == "B") {
		std::vector<std::string> B;
		if (code.at(1).find_first_of("0123456789") != std::string::npos) {
			game.x1.setSatisfaction(std::stoi(code.at(1)));
			game.x2.setSatisfaction(std::stoi(code.at(1)));
			code.erase(code.begin() + 1);
		}
		while (1 + index < code.size()) {
			B.push_back(code.at(1 + index));
			index++;
		}
		while (B.size() > 0) {
			if (std::find(B.begin(), B.end(), "RI") != B.end()) {
				int position = std::find(B.begin(), B.end(), "RI") - B.begin();
				RI(game, 1, B.at(position + 1));
				RI(game, 2, B.at(position + 1));
				B.erase(B.begin() + position, B.begin() + position + 2);
			}
			if (std::find(B.begin(), B.end(), "RK") != B.end()) {
				int position = std::find(B.begin(), B.end(), "RK") - B.begin();
				RK(game, 1);
				RK(game, 2);
				B.erase(B.begin() + position);
			}
			if (std::find(B.begin(), B.end(), "RR") != B.end()) {
				int position = std::find(B.begin(), B.end(), "RR") - B.begin();
				RR(game, 1);
				RR(game, 2);
				B.erase(B.begin() + position);
			}
			if (std::find(B.begin(), B.end(), "SI") != B.end()) {
				int position = std::find(B.begin(), B.end(), "SI") - B.begin();
				game = SI(game, 1, B.at(position + 1));
				game = SI(game, 2, B.at(position + 1));
				B.erase(B.begin() + position, B.begin() + position + 2);
			}
			if (std::find(B.begin(), B.end(), "DD") != B.end()) {
				int position = std::find(B.begin(), B.end(), "DD") - B.begin();
				game = DD(game, 1, B.at(position + 1));
				game = DD(game, 2, B.at(position + 1));
				B.erase(B.begin() + position, B.begin() + position + 2);
			}
			if (std::find(B.begin(), B.end(), "RE") != B.end()) {
				int position = std::find(B.begin(), B.end(), "RE") - B.begin();
				game = RE(game, 1, B.at(position + 1));
				game = RE(game, 2, B.at(position + 1));
				B.erase(B.begin() + position, B.begin() + position + 2);
			}
			if (std::find(B.begin(), B.end(), "CO") != B.end()) {
				int position = std::find(B.begin(), B.end(), "CO") - B.begin();
				game = CO(game, 1);
				game = CO(game, 2);
				B.erase(B.begin() + position);
			}
			if (std::find(B.begin(), B.end(), "SWO") != B.end()) {
				int position = std::find(B.begin(), B.end(), "SWO") - B.begin();
				game = SWO(game);
				B.erase(B.begin() + position);
			}

		}
		code.erase(code.begin(), code.begin() + index + 1);
		return game;
	}
	
	index = 0;
	if (std::find(code.begin(), code.end(), "OT") != code.end()) {
		std::vector<std::string> OT;
		int other = std::find(code.begin(), code.end(), "OT") - code.begin();
		if (code.at(other + 1).find_first_of("0123456789") != std::string::npos) {
			if (chooser == 2) {
				game.x1.setSatisfaction(std::stoi(code.at(other + 1)));
			}
			else {
				game.x2.setSatisfaction(std::stoi(code.at(other + 1)));
			}
			code.erase(code.begin() + other + 1);
		}
		while (other + 1 + index < code.size()) {
			OT.push_back(code.at(other + 1 + index));
			index++;
		}

		while (OT.size() > 0) {
			if (std::find(OT.begin(), OT.end(), "DR") != OT.end()) {
				int position = std::find(OT.begin(), OT.end(), "DR") - OT.begin();
				game = drawScene(game, chooser, "OT", OT.at(position + 1));
				OT.erase(OT.begin() + position, OT.begin() + position + 2);
			}
			if (std::find(OT.begin(), OT.end(), "SI") != OT.end()) {
				int position = std::find(OT.begin(), OT.end(), "SI") - OT.begin();
				if (chooser == 1) {

					game = SI(game, 2, OT.at(position + 1));
				}
				else {
					game = SI(game, 1, OT.at(position + 1));

				}

				OT.erase(OT.begin() + position, OT.begin() + position + 2);
			}
			if (std::find(OT.begin(), OT.end(), "SO") != OT.end()) {
				int position = std::find(OT.begin(), OT.end(), "SO") - OT.begin();
				if (chooser == 1) {
					game = SO(game, 2, OT.at(position + 1));
				}
				else {
					game = SO(game, 1, OT.at(position + 1));
				}
				OT.erase(OT.begin() + position, OT.begin() + position + 2);
			}
			if (std::find(OT.begin(), OT.end(), "DD") != OT.end()) {
				int position = std::find(OT.begin(), OT.end(), "DD") - OT.begin();
				if (chooser == 1) {
					game = DD(game, 2, OT.at(position + 1));
				}
				else {
					game = DD(game, 1, OT.at(position + 1));
				}
				OT.erase(OT.begin() + position, OT.begin() + position + 2);
			}
			if (std::find(OT.begin(), OT.end(), "RE") != OT.end()) {
				int position = std::find(OT.begin(), OT.end(), "RE") - OT.begin();
				if (chooser == 1) {
					game = RE(game, 2, OT.at(position + 1));
				}
				else {
					game = RE(game, 1, OT.at(position + 1));
				}
				OT.erase(OT.begin() + position, OT.begin() + position + 2);
			}
		}
		code.erase(code.begin() + other, code.begin() + other + index + 1);
	}
	index = 0;
	if (std::find(code.begin(), code.end(), "CH") != code.end()) {
		std::vector<std::string> CH;

		//chooser action
		if (code.at(1).find_first_of("0123456789") != std::string::npos) {
			if (chooser == 1) {
				game.x1.setSatisfaction(std::stoi(code.at(1)));
			}
			else {
				game.x2.setSatisfaction(std::stoi(code.at(1)));
			}
			code.erase(code.begin() + 1);
		}
		while (1 + index < code.size()) {
			CH.push_back(code.at(1 + index));
			index++;

		}
		while (CH.size() > 0) {
			if (std::find(CH.begin(), CH.end(), "DR") != CH.end()) {
				int position = std::find(CH.begin(), CH.end(), "DR") - CH.begin();
				game = drawScene(game, chooser, "CH", CH.at(position + 1));
				CH.erase(CH.begin() + position, CH.begin() + position + 2);

			}
			if (std::find(CH.begin(), CH.end(), "RD") != CH.end()) {
				int position = std::find(CH.begin(), CH.end(), "RD") - CH.begin();
				game = RD(game, chooser);
				CH.erase(CH.begin() + position);
			}
			if (std::find(CH.begin(), CH.end(), "RR") != CH.end()) {
				int position = std::find(CH.begin(), CH.end(), "RR") - CH.begin();
				RR(game, chooser);
				CH.erase(CH.begin() + position);
			}
			if (std::find(CH.begin(), CH.end(), "SI") != CH.end()) {
				int position = std::find(CH.begin(), CH.end(), "SI") - CH.begin();
				if (position != 0 && CH.at(position - 1) == "MAY") {
					std::cout << "Choose if you want to swap in Dominant: 1 = Yes. 2 = No.\n";
					int temp = select(2);
					if (temp == 0) {
						game = SI(game, chooser, CH.at(position + 1));
					}
					CH.erase(CH.begin() + position - 1, CH.begin() + position + 2);
				}
				else {
					game = SI(game, chooser, CH.at(position + 1));
					CH.erase(CH.begin() + position, CH.begin() + position + 2);
				}
				
			}
			if (std::find(CH.begin(), CH.end(), "SO") != CH.end()) {
				int position = std::find(CH.begin(), CH.end(), "SO") - CH.begin();
				if (chooser == 1) {
					game = SO(game, 1, CH.at(position + 1));
				}
				else {
					game = SO(game, 2, CH.at(position + 1));
				}
				CH.erase(CH.begin() + position, CH.begin() + position + 2);
			}
			if (std::find(CH.begin(), CH.end(), "DD") != CH.end()) {
				int position = std::find(CH.begin(), CH.end(), "DD") - CH.begin();
				if (chooser == 1) {
					game = DD(game, 1, CH.at(position + 1));
				}
				else {
					game = DD(game, 2, CH.at(position + 1));
				}
				CH.erase(CH.begin() + position, CH.begin() + position + 2);
			}
			if (std::find(CH.begin(), CH.end(), "RE") != CH.end()) {
				
				int position = std::find(CH.begin(), CH.end(), "RE") - CH.begin();
				if (chooser == 1) {
					game = RE(game, 1, CH.at(position + 1));
				}
				else {
					game = RE(game, 2, CH.at(position + 1));
				}
				CH.erase(CH.begin() + position, CH.begin() + position + 2);
			}
			if (std::find(CH.begin(), CH.end(), "DS") != CH.end()) {
				int position = std::find(CH.begin(), CH.end(), "DS") - CH.begin();
				if (chooser == 1) {
					game = DS(game, 1, CH.at(position + 1));
				}
				else {
					game = DS(game, 2, CH.at(position + 1));
				}
				CH.erase(CH.begin() + position, CH.begin() + position + 2);
			}
			code.erase(code.begin(), code.begin() + index + 1);
		}		
	}
	index = 0;
	if (std::find(code.begin(), code.end(), "PA") != code.end()) {
		std::vector<std::string> PA;
		int other = std::find(code.begin(), code.end(), "PA") - code.begin();
		if (code.at(other + 1).find_first_of("0123456789") != std::string::npos) {
			if (player == 1) {
				game.x1.setSatisfaction(std::stoi(code.at(other + 1)));
			}
			else {
				game.x2.setSatisfaction(std::stoi(code.at(other + 1)));
			}
			code.erase(code.begin() + other + 1);
		}
		while (other + 1 + index < code.size()&&code.at(other+1+index)!="PL") {
			PA.push_back(code.at(other + 1 + index));
			index++;
		}
		while (PA.size() > 0) {
			if (std::find(PA.begin(), PA.end(), "DD") != PA.end()) {
				int position = std::find(PA.begin(), PA.end(), "DD") - PA.begin();
				if (player == 1) {
					game = DD(game, 2, PA.at(position + 1));
				}
				else {
					game = DD(game, 1, PA.at(position + 1));
				}
				PA.erase(PA.begin() + position, PA.begin() + position + 2);
			}
			if (std::find(PA.begin(), PA.end(), "RE") != PA.end()) {
				int position = std::find(PA.begin(), PA.end(), "RE") - PA.begin();
				if (player == 1) {
					game = RE(game, 2, PA.at(position + 1));
				}
				else {
					game = RE(game, 1, PA.at(position + 1));
				}
				PA.erase(PA.begin() + position, PA.begin() + position + 2);
			}
		}
		code.erase(code.begin() + other, code.begin() + other + index + 1);
	}

	index = 0;
	if (std::find(code.begin(), code.end(), "PL") != code.end()) {
		std::vector<std::string> PL;
		int other = std::find(code.begin(), code.end(), "PL") - code.begin();
		//chooser action
		if (code.at(other + 1).find_first_of("0123456789") != std::string::npos) {
			if (player == 1) {
				game.x1.setSatisfaction(std::stoi(code.at(other + 1)));
			}
			else {
				game.x2.setSatisfaction(std::stoi(code.at(other + 1)));
			}
			code.erase(code.begin() + 1);
		}
		while (other + 1 + index < code.size() && code.at(index) != ""&&code.at(other + 1 + index) != "PL") {
			PL.push_back(code.at(1 + index));
			index++;
		}
		while (PL.size() > 0) {
			if (std::find(PL.begin(), PL.end(), "DR") != PL.end()) {
				int position = std::find(PL.begin(), PL.end(), "DR") - PL.begin();
				game = drawScene(game, player, "CH", PL.at(position + 1));
				PL.erase(PL.begin() + position, PL.begin() + position + 2);

			}
			if (std::find(PL.begin(), PL.end(), "DD") != PL.end()) {
				int position = std::find(PL.begin(), PL.end(), "DD") - PL.begin();
				game = DD(game, player, PL.at(position + 1));
				PL.erase(PL.begin() + position, PL.begin() + position + 2);
			}
			if (std::find(PL.begin(), PL.end(), "RE") != PL.end()) {
				int position = std::find(PL.begin(), PL.end(), "RE") - PL.begin();
				game = RE(game, player, PL.at(position + 1));
				PL.erase(PL.begin() + position, PL.begin() + position + 2);
			}
			if (std::find(PL.begin(), PL.end(), "CO") != PL.end()) {
				int position = std::find(PL.begin(), PL.end(), "CO") - PL.begin();
				game = CO(game, player);
				PL.erase(PL.begin() + position);
			}
		}
		code.erase(code.begin() + other, code.begin() + other + index + 1);
	}
	return game;
};



Session resolveAddi(Session game, int turn, Scene scene, int c1, int c2) {
	int position = matchChoice(scene, c1, c2, turn);
	if (position == -1) { return game; };
	std::vector<std::string> effects = scene.getAddis().at(position).getCode();
	//std::cout << effects.at(0)+"\n";
	effects.erase(effects.begin());
	codePlayer cp = resolveCABCD(turn, scene, c1, c2, effects);
	int chooser = cp.chooser;
	return resolveChoice(game, chooser, turn, cp.code);
};

int matchChoice(Scene scene, int c1, int c2, int player) {
	std::vector<std::string> matches = match2(c1, c2, player);
	for (int i = 0; i < scene.getAddis().size(); i++) {
		std::string c = scene.getAddis().at(i).getCode().at(0);
		
		if (std::find(matches.begin(), matches.end(), c) != matches.end()) {
			//std::cout << c;
			return i;
		}
	}
	return -1;
};

std::vector<std::string> match2(int c1, int c2, int player) {
	if (c1 == 0 && c2 == 0) {
		//AA
		return { "MA", "MAB", "MABC", "M/CDE", "M", "E" };
	}
	else if (c1 == 0 && c2 == 1 || c2 == 0 && c1 == 1) {
		//AB/BA
		return { "CAB", "CAE", "NM", "E" };
	}
	else if (c1 == 0 && c2 == 2 && player == 1 || c2 == 0 && c1 == 2 && player == 2) {
		//AC
		return { "CAC", "CAB-CDP", "CAB-CD", "CAE", "CCE", "NM", "E" };
	}
	else if (c1 == 0 && c2 == 2 && player == 2 || c2 == 0 && c1 == 2 && player == 1) {
		//CA
		
		return { "CAC", "CCD-ABP", "CAB-CD", "CAE", "CCE", "NM", "E"};
	}
	else if (c1 == 0 && c2 == 3 && player == 1 || c2 == 0 && c1 == 3 && player == 2) {
		//AD
		return { "M/CDE", "CAB-CDP", "CAB-CD", "CD-AB", "M/CDE", "CAE", "CDE", "NM", "E" };
	}
	else if (c1 == 0 && c2 == 3 && player == 2 || c2 == 0 && c1 == 3 && player == 1) {
		//DA
		return { "M/CDE", "CCD-ABP", "CAB-CD", "CD-AB", "M/CDE", "CAE", "CDE", "NM", "E" };
	}
	else if (c1 == 1 && c2 == 1) {
		//BB
		return { "MB", "MBC", "M", "MAB", "MABC", "M/CDE", "E" };
	}
	else if (c1 == 1 && c2 == 2 && player == 1 || c2 == 1 && c1 == 2 && player == 2) {
		//BC
		return { "CBC", "CB-CD", "CAB-CD", "CAB-CDP", "CCE", "NM", "E" };
	}
	else if (c1 == 1 && c2 == 2 && player == 2 || c2 == 1 && c1 == 2 && player == 1) {
		//CB
		return { "CBC", "CB-CD", "CAB-CD", "CCD-ABP", "CCE", "NM", "E" };
	}
	else if (c1 == 1 && c2 == 3 && player == 1 || c2 == 1 && c1 == 3 && player == 2) {
		//BD
		return { "M/CDE", "CBD/MD", "CB-CD", "CAB-CD", "CD-AB", "CAB-CDP", "CDE", "NM", "E" };
	}
	else if (c1 == 1 && c2 == 3 && player == 2 || c2 == 1 && c1 == 3 && player == 1) {
		//DB
		return { "M/CDE", "CBD/MD", "CB-CD", "CAB-CD", "CD-AB", "CCD-ABP", "CDE", "NM", "E" };
	}
	else if (c1 == 2 && c2 == 2) {
		//CC
		return { "MC", "MBC", "M", "MAB", "MABC", "M/CDE", "E" };
	}
	else if (c1 == 2 && c2 == 3 && player == 1 || c2 == 2 && c1 == 3 && player == 2) {
		//CD
		return { "M/CDE", "CCD", "CCE", "CDE", "NM", "E" };
	}
	else if (c1 == 2 && c2 == 3 && player == 2 || c1 == 3 && c2 == 2 && player == 1) {
		//DC
		return { "CD-CP", "M/CDE", "CCD", "CCE", "CDE", "NM", "E" };
	}
	else if (c1 == 3 && c2 == 3) {
		//DD
		return { "MD", "M/CDE", "CBD-MD", "M", "E" };
	}


};

codePlayer resolveCABCD(int turn, Scene scene, int c1, int c2, std::vector<std::string> code) {
	int chooser = 1;
	if (std::find(code.begin(), code.end(), "CA") != code.end()) {

		int position = std::find(code.begin(), code.end(), std::string("CA")) - code.begin();
		
		if (c1 == 0) {
			chooser = 1;
			replace(code.begin(), code.end(), "CA", "PL");
		}
		else {
			chooser = 2;
			replace(code.begin(), code.end(), "CA", "PA");
		}

	}
	if (std::find(code.begin(), code.end(), "CB") != code.end()) {
		replace(code.begin(), code.end(), "CB", "OT");
	}
	if (std::find(code.begin(), code.end(), "CC") != code.end()) {
		if (c1 == 2) {
			chooser = 1;
			replace(code.begin(), code.end(), "CC", "PL");
		}
		else {
			chooser = 2;
			replace(code.begin(), code.end(), "CC", "PA");
		}

	}
	if (std::find(code.begin(), code.end(), "CD") != code.end()) {
		int position = std::find(code.begin(), code.end(), std::string("CD")) - code.begin();
		replace(code.begin(), code.end(), "CD", "CH");
		if (c1 == 3) {
			chooser = 1;
		}
		else {
			chooser = 2;
		}
	}
	if (std::find(code.begin(), code.end(), "A/B") != code.end()) {
		if (std::find(code.begin(), code.end(), "A/B") != code.end()) {
			int position = std::find(code.begin(), code.end(), "A/B") - code.begin();
			replace(code.begin(), code.end(), std::string("A/B"), std::string("CH"));
			replace(code.begin(), code.end(), std::string("C/D"), std::string("OT"));
			if (c1 == 2 || c1 == 3) {
				chooser = 1;
			}
			else {
				chooser = 2;
			}
		}
	}

	return codePlayer{ code, chooser };
};
