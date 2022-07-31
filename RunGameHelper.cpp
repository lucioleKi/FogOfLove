#include "RunGameHelper.h"

Session specialOp(Session session, int index, Deck deck, int turn, Scene scene) {
	if (index == 26 && deck == Sweet) {
		if (turn == 1) {
			session.per.change(1, 4, 1);
			scene.setLine(scene.getLine() + "\nPLAYER Extroversion + 1.");
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

	else if (index == 13 && deck == Drama || index == 10 && deck == Drama) {
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
	else if (index == 35 && deck == Sweet) {
		if (turn == 1) {
			session.per.change(1, 10, 1);
			scene.setLine(scene.getLine() + "\nPLAYER Sincerity + 1.");
			std::cout << scene.printFull();
		}
		else {
			session.per.change(2, 10, 1);
			scene.setLine(scene.getLine() + "\nPLAYER Sincerity + 1.");
			std::cout << scene.printFull();
		}
	}
	else if (index == 28 && deck == Serious) {
		if (turn == 1) {
			session.per.change(1, 10, 1);
			session.per.change(1, 0, 1);
			scene.setLine(scene.getLine() + "\nPLAYER Sincerity + 1, Discipline + 1.");
			std::cout << scene.printFull();
		}
		else {
			session.per.change(2, 10, 1);
			session.per.change(2, 0, 1);
			scene.setLine(scene.getLine() + "\nPLAYER Sincerity + 1, Discipline + 1.");
			std::cout << scene.printFull();
		}
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

Session drawStarting(Session game) {
	int sweet = game.plot.getStarting().at(0);
	int serious = game.plot.getStarting().at(1);
	int drama = game.plot.getStarting().at(2);
	for (int i = 0; i < sweet; i++) {
		game.hand1.push_back(game.sweetS.at(0));
		game.hand2.push_back(game.sweetS.at(1));
		game.sweetS.erase(game.sweetS.begin(), game.sweetS.begin() + 2);
	}
	for (int i = 0; i < serious; i++) {
		game.hand1.push_back(game.seriousS.at(0));
		game.hand2.push_back(game.seriousS.at(1));
		game.seriousS.erase(game.seriousS.begin(), game.seriousS.begin() + 2);
	}
	for (int i = 0; i < drama; i++) {
		game.hand1.push_back(game.dramaS.at(0));
		game.hand2.push_back(game.dramaS.at(1));
		game.dramaS.erase(game.dramaS.begin(), game.dramaS.begin() + 2);
	}

	return game;
};

Session drawFill(Session session, Deck d) {
	while (session.hand1.size() < 5) {
		switch (d)
		{
		case Sweet:
			session.hand1.push_back(session.sweetS.at(0));
			session.sweetS.erase(session.sweetS.begin());
		case Serious:
			session.hand1.push_back(session.seriousS.at(0));
			session.seriousS.erase(session.seriousS.begin());
			break;
		case Drama:
			session.hand1.push_back(session.dramaS.at(0));
			session.dramaS.erase(session.dramaS.begin());
			break;
		}
	}
	while (session.hand2.size() < 5) {
		switch (d)
		{
		case Sweet:
			session.hand2.push_back(session.sweetS.at(0));
			session.sweetS.erase(session.sweetS.begin());
		case Serious:
			session.hand2.push_back(session.seriousS.at(0));
			session.seriousS.erase(session.seriousS.begin());
			break;
		case Drama:
			session.hand2.push_back(session.dramaS.at(0));
			session.dramaS.erase(session.dramaS.begin());
			break;
		}
	}
	return session;
};

int chooseScene(Session session, int turn) {
	if (turn == 1) {
		for (int i = 0; i < 5; i++) {
			//std::cout << session.hand1.at(i).printFull();
			std::cout << session.hand1.at(i).getTitle();
		}
		return select(5);
	}
	else {
		for (int i = 0; i < 5; i++) {
			//std::cout << session.hand2.at(i).printFull();
			std::cout << session.hand2.at(i).getTitle();
		}
		return select(5);
	}
};

Session chooseDestiny(Session session) {
	int index = 0;
	int temp = 8;
	std::vector<int> hand;
	
		
		for (int i = 0; i < session.d1.size(); i++) {
			if (session.d1.at(i).getIn()) {
				std::cout << session.d1.at(i).printFull();
				session.d1.at(i).changeIn();
				hand.push_back(i);
				index++;
			}
		}
		std::cout << session.x1.getName()+", select a final DESTINY:\n";
		temp = select(index);
		session.d1.at(hand.at(temp)).changeIn();
		hand.clear();
		for (int i = 0; i < session.d2.size(); i++) {
			if (session.d2.at(i).getIn()) {
				std::cout << session.d2.at(i).printFull();
				session.d2.at(i).changeIn();
				hand.push_back(i);
				index++;
			}
		}
		std::cout << session.x2.getName() + ", select a final DESTINY:\n";
		temp = select(index);
		session.d2.at(hand.at(temp)).changeIn();
	
	
	
	return session;
};

int findDestiny(Session session, int player) {
	if (player == 1) {
		for (int i = 0; i < session.d1.size(); i++) {
			if (session.d1.at(i).getIn()) {
				return i;
			}
		}
	}
	else {
		for (int i = 0; i < session.d2.size(); i++) {
			if (session.d2.at(i).getIn()) {
				return i;
			}
		}
	}
	return 0;
};

int fullfilDestiny(Session session, int player, int destiny1, int destiny2) {
	if (player == 1) {
		switch (destiny1)
		{
		case 0:
			if (session.per.get1(8) - session.per.get1(9) > -3) {
				return 0;
			}
			if (session.x1.getSatisfaction() - session.x2.getSatisfaction() < 15) {
				return 0;
			}
			if (destiny2 == 4 || destiny2 == 5) {
				return 0;
			}
			return 1;
		case 1:
			if (session.x1.getSatisfaction() - session.x2.getSatisfaction() < -3 || session.x1.getSatisfaction() - session.x2.getSatisfaction() > 3) {
				return 0;
			}
			if (session.x1.getSatisfaction() < 20) {
				return 0;
			}
			if (destiny2 == 4 || destiny2 == 5) {
				return 0;
			}
			return 1;
		case 2:
			if (session.per.getShared(8) - session.per.getShared(9) < 6) {
				return 0;
			}
			if (session.x1.getSatisfaction() + session.x2.getSatisfaction() < 60) {
				return 0;
			}
			if (destiny2 == 4 || destiny2 == 5) {
				return 0;
			}
			return 1;
		case 3:
			if (session.per.get1(10) - session.per.get1(11) < 4) {
				return 0;
			}
			if (session.x2.getSatisfaction() < 40) {
				return 0;
			}
			if (destiny2 == 4 || destiny2 == 5) {
				return 0;
			}
			return 1;
		case 4:
			if (destiny2 == 5) {
				return 1;
			}
			if (session.x1.getSatisfaction() < 15) {
				return 0;
			}
			//todo: shared balance opposite of trait goals
			return 1;
		case 5:
			if (session.per.get1(10) - session.per.get1(11) > -4) {
				return 0;
			}
			if (session.x2.getSatisfaction() > 15) {
				return 0;
			}
			if (destiny2 == 4 || destiny2 == 5) {
				return 0;
			}
			return 1;
		}
	}
	else {
		switch (destiny2)
		{
		case 0:
			if (session.per.get2(8) - session.per.get2(9) > -3) {
				return 0;
			}
			if (session.x2.getSatisfaction() - session.x1.getSatisfaction() < 15) {
				return 0;
			}
			if (destiny1 == 4 || destiny1 == 5) {
				return 0;
			}
			return 1;
		case 1:
			if (session.x1.getSatisfaction() - session.x2.getSatisfaction() < -3 || session.x1.getSatisfaction() - session.x2.getSatisfaction() > 3) {
				return 0;
			}
			if (session.x2.getSatisfaction() < 20) {
				return 0;
			}
			if (destiny1 == 4 || destiny1 == 5) {
				return 0;
			}
			return 1;
		case 2:
			if (session.per.getShared(8) - session.per.getShared(9) < 6) {
				return 0;
			}
			if (session.x1.getSatisfaction() + session.x2.getSatisfaction() < 60) {
				return 0;
			}
			if (destiny1 == 4 || destiny1 == 5) {
				return 0;
			}
			return 1;
		case 3:
			if (session.per.get2(10) - session.per.get2(11) < 4) {
				return 0;
			}
			if (session.x1.getSatisfaction() < 40) {
				return 0;
			}
			if (destiny1 == 4 || destiny1 == 5) {
				return 0;
			}
			return 1;
		case 4:
			if (destiny1 == 5) {
				return 1;
			}
			if (session.x2.getSatisfaction() < 15) {
				return 0;
			}
			//todo: shared balance opposite of trait goals
			return 1;
		case 5:
			if (session.per.get2(10) - session.per.get2(11) > -4) {
				return 0;
			}
			if (session.x1.getSatisfaction() > 15) {
				return 0;
			}
			if (destiny1 == 4 || destiny1 == 5) {
				return 0;
			}
			return 1;
		}
	}
	
};

Session unrevealedSecrets(Session session) {
	int turn = 1;
	if (session.secret1.size() == 0) {
		turn = 2;
	}
	
	while (session.secret1.size() > 0 || session.secret2.size() > 0) {
		if (turn==1) {
			Scene secret = session.secret1.at(0);
			std::cout << secret.printFull();
			Additional a = secret.getAddis().at(0);
			session = resolveChoice(session, 1, 1, a.getCode());
			session = specialSecrets(session, secret, turn);
			session.secret1.erase(session.secret1.begin());
			if (session.secret2.size() > 0) {
				turn = 2;
				
			}
		}
		else {
			Scene secret = session.secret2.at(0);
			std::cout << secret.printFull();
			Additional a = secret.getAddis().at(0);
			session = resolveChoice(session, 2, 2, a.getCode());
			session = specialSecrets(session, secret, turn);
			session.secret2.erase(session.secret2.begin());
			if (session.secret1.size() > 0) {
				turn = 1;
				
			}
		}
		std::cout<<std::to_string(session.x1.getSatisfaction());
		std::cout<<std::to_string(session.x2.getSatisfaction());
	}
	return session;
};

Session specialSecrets(Session session, Scene secret, int player) {
	if (secret.getIndex() == 35) {
		if (!session.d1.at(4).getIn() && !session.d1.at(5).getIn() && !session.d2.at(4).getIn() && !session.d2.at(5).getIn()) {
			session.x1.setSatisfaction(4);
			session.x2.setSatisfaction(4);
		}
	}
	else if (secret.getIndex() == 27) {
		if (player == 1) {
			if (!session.d1.at(6).getIn()) {
				std::cout << session.x1.getName()+", do you choose to swap in SELF-REALIZATION and use it as your final DESTINY? \n1=Yes\n2=No\n";
				int temp = select(2);
				if (temp == 0) {
					session.d1.at(findDestiny(session, 1)).changeIn();
					session.d1.at(6).changeIn();
				}
			}
		}
		else {
			if (!session.d2.at(6).getIn()) {
				std::cout << session.x2.getName() + ", do you choose to swap in SELF-REALIZATION and use it as your final DESTINY? \n1=Yes\n2=No\n";
				int temp = select(2);
				if (temp == 0) {
					session.d2.at(findDestiny(session, 2)).changeIn();
					session.d2.at(6).changeIn();
				}
			}
		}
	}
	else if (secret.getIndex() == 29) {
		if (!session.d1.at(4).getIn() && !session.d1.at(5).getIn() && !session.d2.at(4).getIn() && !session.d2.at(5).getIn()) {
			session.x1.setSatisfaction(2);
			session.x2.setSatisfaction(2);
		}
	}
	else if (secret.getIndex() == 15) {
		if (!session.d1.at(4).getIn() && !session.d1.at(5).getIn() && !session.d2.at(4).getIn() && !session.d2.at(5).getIn()) {
			if (player == 1) {
				session.x1.setSatisfaction(3);
			}
			else {
				session.x2.setSatisfaction(3);
			}
		}
	}
	return session;
};

Session SEEffect(Session session, Scene SE, int player) {
	if(SE.getIndex()==18||SE.getIndex()==20){
		std::cout << session.per.printFull();
		if (player == 1) {
			std::cout << session.x1.getName()+", choose an aspect:\n";
			int temp = select(6);
			session.per.change(2, temp * 2, session.per.get2(temp*2)*(-1));
			session.per.change(2, temp * 2 + 1, session.per.get2(temp * 2 + 1) * (-1));
		}
		else {
			std::cout << session.x2.getName() + ", choose an aspect:\n";
			int temp = select(6);
			session.per.change(1, temp * 2, session.per.get1(temp * 2) * (-1));
			session.per.change(1, temp * 2 + 1, session.per.get1(temp * 2 + 1) * (-1));
		}
		
	}
	else if (SE.getIndex() == 21) {
		int max = session.secret1.size()+session.secret2.size();
		if (max > 0) {
			int temp = rand() / RAND_MAX * max;
			if (temp >= session.secret1.size()) {
				session.secret2.erase(session.secret2.begin() + temp - session.secret1.size());
			}
			else {
				session.secret1.erase(session.secret1.begin() + temp);
			}
		}
		

		std::cout << session.per.printFull();
		if (player == 1) {
			std::cout << session.x1.getName() + ", choose an aspect:\n";
			int temp = select(6);
			session.per.change(2, temp * 2, session.per.get2(temp * 2) * (-1));
			session.per.change(2, temp * 2 + 1, session.per.get2(temp * 2 + 1) * (-1));
		}
		else {
			std::cout << session.x2.getName() + ", choose an aspect:\n";
			int temp = select(6);
			session.per.change(1, temp * 2, session.per.get1(temp * 2) * (-1));
			session.per.change(1, temp * 2 + 1, session.per.get1(temp * 2 + 1) * (-1));
		}
	}
	return session;
};

Session situationEffect(Session session, Scene situation, int player) {
	
	return session;
};