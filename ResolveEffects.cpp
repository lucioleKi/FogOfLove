#include "ResolveEffects.h"
#include "Enums.h"
#include "Scene.h"
#include "Session.h"
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
	game = resolveSatis(game, 1, c1);
	game = resolveSatis(game, 2, c2);
	
	std::cout << game.per.printFull();
	std::cout << std::to_string(game.x1.getSatisfaction());
	std::cout << std::to_string(game.x2.getSatisfaction());
	return game;
};

Session resolveEffectsP(Session game, int turn, Scene scene, int choice1) {
	
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
	//if (player == 1) {
		//game = resolveSatis(game, 2, c1);
	//}
	//else {
		//game = resolveSatis(game, 1, c1);
	//}
	//std::cout << std::to_string(game.x1.getSatisfaction());
	//std::cout << std::to_string(game.x2.getSatisfaction());
	return game;
};


Session resolveSatis(Session game, int chooser, Choice c) {
	if (chooser == 1) {
		if (c.getChoser() != 0) {
			game.x1.setSatisfaction(c.getChoser());
		}
		if (c.getOther() != 0) {
			game.x2.setSatisfaction(c.getOther());
		}
	}
	else {
		if (c.getChoser() != 0) {
			game.x2.setSatisfaction(c.getChoser());
		}
		if (c.getOther() != 0) {
			game.x1.setSatisfaction(c.getOther());
		}
	}
	return game;
};

Session resolveAddi(Session game, int turn, Scene scene, int c1, int c2) {
	int position = matchChoice(scene, c1, c2, turn);
	if (position == -1) { return game; };
	std::vector<std::string> effects = scene.getAddis().at(position).getCode();
	std::cout << effects.at(0)+"\n";
	effects.erase(effects.begin());
	if (effects.size() > 0) {
		if (effects.at(0) == "B") {
			if (effects.at(1).find_first_of("0123456789") != std::string::npos){
				game.x1.setSatisfaction(std::stoi(effects.at(1)));
				game.x2.setSatisfaction(std::stoi(effects.at(1)));
			}
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
		}
		if (effects.at(0) == "OT") {

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
		return { "CBC", "CB-CD", "CAB-CD", "CAB-CDP", "CCE", "NM", "E"};
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
	else if (c1 == 2 && c2 == 3&&player ==1|| c2 == 2 && c1 == 3 && player == 2) {
		//CD
		return { "M/CDE", "CCD", "CCE", "CDE", "NM", "E"};
	}
	else if (c1 == 2 && c2 == 3 && player == 2|| c1 == 3 && c2 == 2 && player == 1) {
		//DC
		return { "CD-CP", "M/CDE", "CCD", "CCE", "CDE", "NM", "E" };
	}
	else if (c1 == 3 && c2 == 3) {
		//DD
		return {"MD", "M/CDE", "CBD-MD", "M", "E"};
	}
	
	
}