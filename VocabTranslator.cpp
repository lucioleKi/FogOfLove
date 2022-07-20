#include "VocabTranslator.h"


Session drawScene(Session session, int chooser, std::string who, std::string deck) {


	if (who == "OT") {
		if (chooser == 1) {
			if (deck == "Sweet")
			{
				session.hand2.push_back(session.sweetS.at(0));
				session.sweetS.erase(session.sweetS.begin());
			}
			else if (deck == "Serious") {
				session.hand2.push_back(session.seriousS.at(0));
				session.seriousS.erase(session.seriousS.begin());
			}
			else {
				session.hand2.push_back(session.dramaS.at(0));
				session.dramaS.erase(session.dramaS.begin());
			}
		}
		else {
			if (deck == "Sweet")
			{
				session.hand1.push_back(session.sweetS.at(0));
				session.sweetS.erase(session.sweetS.begin());
			}
			else if (deck == "Serious") {
				session.hand1.push_back(session.seriousS.at(0));
				session.seriousS.erase(session.seriousS.begin());
			}
			else {
				session.hand1.push_back(session.dramaS.at(0));
				session.dramaS.erase(session.dramaS.begin());
			}
		}
	}
	else if (who == "CH") {
		std::cout << std::to_string(chooser);
		std::cout << deck;
		if (chooser == 2) {
			if (deck == "Sweet")
			{
				session.hand2.push_back(session.sweetS.at(0));
				session.sweetS.erase(session.sweetS.begin());
			}
			else if (deck == "Serious") {
				std::cout << "getSerious";
				session.hand2.push_back(session.seriousS.at(0));
				session.seriousS.erase(session.seriousS.begin());
			}
			else {
				session.hand2.push_back(session.dramaS.at(0));
				session.dramaS.erase(session.dramaS.begin());
			}
		}
		else {
			if (deck == "Sweet")
			{
				session.hand1.push_back(session.sweetS.at(0));
				session.sweetS.erase(session.sweetS.begin());
			}
			else if (deck == "Serious") {
				session.hand1.push_back(session.seriousS.at(0));
				session.seriousS.erase(session.seriousS.begin());
			}
			else {
				session.hand1.push_back(session.dramaS.at(0));
				session.dramaS.erase(session.dramaS.begin());
			}
		}
	}
	else if (who == "B") {
		if (deck == "Sweet")
		{
			session.hand1.push_back(session.sweetS.at(0));
			session.hand2.push_back(session.sweetS.at(1));
			session.sweetS.erase(session.sweetS.begin(), session.sweetS.begin() + 2);
		}
		else if (deck == "Serious") {
			session.hand1.push_back(session.seriousS.at(0));
			session.hand2.push_back(session.seriousS.at(1));
			session.seriousS.erase(session.seriousS.begin(), session.seriousS.begin() + 2);
		}
		else {
			session.hand1.push_back(session.dramaS.at(0));
			session.hand2.push_back(session.dramaS.at(1));
			session.dramaS.erase(session.dramaS.begin(), session.dramaS.begin() + 2);
		}
	}


	return session;
};

Session RD(Session session, int chooser) {
	std::vector<int> hand;
	if (chooser == 1) {
		int index = 1;
		for (int i = 0; i < session.d1.size(); i++) {
			if (session.d1.at(i).getIn()) {
				std::cout << std::to_string(index)+" = " +session.d1.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}
		std::cout << "Choose 1 DESTINY to reveal and then discard:\n";
		int temp = select(index);
		session.d1.at(hand.at(temp)).changeIn();
		if (!session.d1.at(hand.at(temp)).getIn()) {
			std::cout << session.d1.at(hand.at(temp)).getName();
		}
	}
	else {
		int index = 1;
		for (int i = 0; i < session.d2.size(); i++) {
			if (session.d2.at(i).getIn()) {
				std::cout << std::to_string(index) + " = " + session.d2.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}
		std::cout << "Choose 1 DESTINY to reveal and then discard:\n";
		int temp = select(index);
		session.d2.at(hand.at(temp)).changeIn();
		if (!session.d2.at(hand.at(temp)).getIn()) {
			std::cout << session.d2.at(hand.at(temp)).getName();
		}
	}
	return session;
};

void RI(Session session, int player, std::string destiny) {
	if (player == 1) {
		for (int i = 0; i < session.d1.size(); i++) {
			if (session.d1.at(i).getName() == destiny && session.d1.at(i).getIn()) {
				std::cout << session.x1.getName() + " has " + destiny + " in hand.\n";
				return;
			}
		}
		std::cout << session.x1.getName() + " does not have " + destiny + " in hand.\n";
		return;
	}
	else {
		for (int i = 0; i < session.d2.size(); i++) {
			if (session.d2.at(i).getName() == destiny && session.d2.at(i).getIn()) {
				std::cout << session.x2.getName() + " has " + destiny + " in hand.\n";
				return;
			}
		}
		std::cout << session.x2.getName() + " does not have " + destiny + " in hand.\n";
		return;
	}
	
};