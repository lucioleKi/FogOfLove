#include "ResolveEffects.h"
#include "Enums.h"
#include "Scene.h"
#include "Session.h"
#include "VocabTranslator.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

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
	game = resolveChoice(game, 1, turn, c1.getCode());
	game = resolveChoice(game, 2, turn, c2.getCode());
	
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

	if (std::find(code.begin(), code.end(), "OT") != code.end()) {
		std::vector<std::string> OT;
		int other = std::find(code.begin(), code.end(), "OT")-code.begin();
		if (code.at(other+1).find_first_of("0123456789") != std::string::npos) {
			if (chooser == 2) {
				game.x1.setSatisfaction(std::stoi(code.at(other+1)));
			}
			else {
				game.x2.setSatisfaction(std::stoi(code.at(other+1)));
			}
			code.erase(code.begin()+other + 1);
		}
		while (other + 1+index< code.size()) {
			OT.push_back(code.at(other+1+index));
			index++;
		}
		
		while (OT.size() > 0) {
			if (std::find(OT.begin(), OT.end(), "DR") != OT.end()) {
				int position = std::find(OT.begin(), OT.end(), "DR") - OT.begin();
				game = drawScene(game, chooser, "OT", OT.at(position + 1));
				OT.erase(OT.begin() + position, OT.begin() + position + 2);
			}
		}
		code.erase(code.begin() + other);
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
		while (1+index< code.size()) {
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
			
		}
		code.erase(code.begin());
	}
	
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
		while (other + 1 + index < code.size()) {
			PA.push_back(code.at(other + 1 + index));
			index++;
		}
		
		code.erase(code.begin() + other);
	}

	if (std::find(code.begin(), code.end(), "PL") != code.end()) {
		std::vector<std::string> PL;

		//chooser action
		if (code.at(1).find_first_of("0123456789") != std::string::npos) {
			if (player == 1) {
				game.x1.setSatisfaction(std::stoi(code.at(1)));
			}
			else {
				game.x2.setSatisfaction(std::stoi(code.at(1)));
			}
			code.erase(code.begin() + 1);
		}
		while (1 + index < code.size()&&code.at(index)!="") {
			PL.push_back(code.at(1 + index));
			index++;
		}
		while (PL.size() > 0) {
			if (std::find(PL.begin(), PL.end(), "DR") != PL.end()) {
				
				int position = std::find(PL.begin(), PL.end(), "DR") - PL.begin();
				game = drawScene(game, player, "CH", PL.at(position + 1));
				PL.erase(PL.begin() + position, PL.begin() + position + 2);
				
			}
		}
		code.erase(code.begin());
	}
	
	

	if (std::find(code.begin(), code.end(), "B") != code.end()) {
		std::vector<std::string> B;
		if (code.at(1).find_first_of("0123456789") != std::string::npos) {
			game.x1.setSatisfaction(std::stoi(code.at(1)));
			game.x2.setSatisfaction(std::stoi(code.at(1)));
		}
		while (1+index< code.size()) {
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
		}
		code.erase(code.begin());
	}
	return game;
};



Session resolveAddi(Session game, int turn, Scene scene, int c1, int c2) {
	int position = matchChoice(scene, c1, c2, turn);
	if (position == -1) { return game; };
	std::vector<std::string> effects = scene.getAddis().at(position).getCode();
	//std::cout << effects.at(0)+"\n";
	effects.erase(effects.begin());
	return resolveChoice(game, 1, turn, effects);
	
	
	effects.erase(effects.begin());
	if (effects.size() > 0) {
		if (effects.at(0) == "B") {
			if (effects.at(1).find_first_of("0123456789") != std::string::npos){
				game.x1.setSatisfaction(std::stoi(effects.at(1)));
				game.x2.setSatisfaction(std::stoi(effects.at(1)));
			}
			effects.erase(effects.begin() + 1);
		}
		if (effects.at(0) == "PL") {
			if (turn == 1) {
				if (effects.at(1).find_first_of("0123456789") != std::string::npos) {
					game.x1.setSatisfaction(std::stoi(effects.at(1)));
				}
			}
			else {
				if (effects.at(1).find_first_of("0123456789") != std::string::npos) {
					game.x2.setSatisfaction(std::stoi(effects.at(1)));
				}
			}
			effects.erase(effects.begin() + 1);
		}
		if (effects.at(0) == "PA") {
			if (turn == 2) {
				if (effects.at(1).find_first_of("0123456789") != std::string::npos) {
					game.x1.setSatisfaction(std::stoi(effects.at(1)));
				}
			}
			else {
				if (effects.at(1).find_first_of("0123456789") != std::string::npos) {
					game.x2.setSatisfaction(std::stoi(effects.at(1)));
				}
			}
			effects.erase(effects.begin() + 1);
		}
		if (effects.at(0) == "OT") {
			if (turn == 1) {
				if (effects.at(1).find_first_of("0123456789") != std::string::npos) {
					game.x1.setSatisfaction(std::stoi(effects.at(1)));
				}
			}
			else {
				if (effects.at(1).find_first_of("0123456789") != std::string::npos) {
					game.x2.setSatisfaction(std::stoi(effects.at(1)));
				}
			}
			effects.erase(effects.begin() + 1);
		}
	}
	
	std::cout << std::to_string(game.x1.getSatisfaction());
	std::cout << std::to_string(game.x2.getSatisfaction());
	return game;
};

int matchChoice(Scene scene, int c1, int c2, int player) {
	std::vector<std::string> matches = match2(c1, c2, player);
	for (int i = 0; i < scene.getAddis().size(); i++) {
		std::string c = scene.getAddis().at(i).getCode().at(0);
		if (std::find(matches.begin(), matches.end(), c) != matches.end()) {
			return i;
		}
	}
	return -1;
};

std::vector<std::string> match2(int c1, int c2, int player) {
	if (c1 == 0 && c2 == 0) {
		//AA
		return { "MA", "M", "MAB", "MABC", "M/CDE", "E" };
	}
	else if (c1 == 0 && c2 == 1 || c2 == 0 && c1 == 1) {
		//AB/BA
		return { "CAB", "CAE", "NM", "E" };
	}
	else if (c1 == 0 && c2 == 2 && player == 1 || c2 == 0 && c1 == 2 && player == 2) {
		//AC
		return { "CAB-CDP", "CAB-CD", "CAE", "CCE", "NM", "E" };
	}
	else if (c1 == 0 && c2 == 2 && player == 2 || c2 == 0 && c1 == 2 && player == 1) {
		//CA
		return { "CCD-ABP", "CAB-CD", "CAE", "CCE", "NM", "E" };
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
		return { "MB", "M", "MAB", "MABC", "M/CDE", "E" };
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
		return { "MC", "M", "MAB", "MABC", "M/CDE", "E" };
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


