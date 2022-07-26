#include "RunGameHelper.h"

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
			std::cout << session.hand1.at(i).printFull();
		}
		return select(5);
	}
	else {
		for (int i = 0; i < 5; i++) {
			std::cout << session.hand1.at(i).printFull();
		}
		return select(5);
	}
};

int chooseDestiny(Session session, int player) {
	int index = 0;
	std::vector<int> hand;
	if (player == 1) {
		
		for (int i = 0; i < session.d1.size(); i++) {
			if (session.d1.at(i).getIn()) {
				std::cout << session.d1.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}
		std::cout << session.x1.getName()+", select a final DESTINY:\n";
	}
	else {
		for (int i = 0; i < session.d2.size(); i++) {
			if (session.d2.at(i).getIn()) {
				std::cout << session.d2.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}
		std::cout << session.x2.getName() + ", select a final DESTINY:\n";
	}
	
	int temp = select(index);
	return hand.at(temp);
};