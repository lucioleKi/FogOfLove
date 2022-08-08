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
		if (chooser == 2) {
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
		std::cout << session.x1.getName() + " has the following DESTINIES in hand:\n";
		int index = 0;
		for (int i = 0; i < session.d1.size(); i++) {
			if (session.d1.at(i).getIn()) {
				std::cout << std::to_string(index+1)+" = " +session.d1.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}
		if (hand.size() == 2) {
			std::cout << "You only have 2 DESTINIES in hand. You cannot discard a DESTINY now.\n";
			return session;
		}
		std::cout << session.x1.getName()+", choose 1 DESTINY to reveal and then discard:\n";
		int temp = select(index);
		session.d1.at(hand.at(temp)).changeIn();
		if (!session.d1.at(hand.at(temp)).getIn()) {
			std::cout << session.d1.at(hand.at(temp)).getName();
		}
	}
	else {
		std::cout << session.x2.getName() + " has the following DESTINIES in hand:\n";
		int index = 0;
		for (int i = 0; i < session.d2.size(); i++) {
			if (session.d2.at(i).getIn()) {
				std::cout << std::to_string(index+1) + " = " + session.d2.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}
		if (hand.size() == 2) {
			std::cout << "You only have 2 DESTINIES in hand. You cannot discard a DESTINY now.\n";
			return session;
		}
		std::cout << session.x2.getName()+", choose 1 DESTINY to reveal and then discard:\n";
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

void RK(Session session, int player) {
	std::vector<int> hand;
	if (player == 1) {
		std::cout << session.x1.getName() + " has the following DESTINIES in hand:\n";
		int index = 0;
		for (int i = 0; i < session.d1.size(); i++) {

			if (session.d1.at(i).getIn()) {
				std::cout << session.d1.at(i).printFull();
				hand.push_back(i);
				index++;
			}
			
		}
		std::cout <<session.x1.getName()+ ", choose 1 DESTINY to reveal:\n";
		int temp = select(index);
		std::cout << session.d1.at(hand.at(temp)).printFull();
	}
	else {
		std::cout << session.x2.getName() + " has the following DESTINIES in hand:\n";
		int index = 0;
		for (int i = 0; i < session.d2.size(); i++) {
			if (session.d2.at(i).getIn()) {
				std::cout << session.d2.at(i).printFull();
				hand.push_back(i);
				index++;
			}
			
		}
		std::cout << session.x2.getName() + ", choose 1 DESTINY to reveal:\n";
		int temp = select(index);
		std::cout << session.d2.at(hand.at(temp)).printFull();
	}
	return;
};

void RR(Session session, int player) {
	std::vector<int> hand;
	srand(time(0));
	if (player == 1) {
		int index = 0;
		for (int i = 0; i < session.d1.size(); i++) {
			if (session.d1.at(i).getIn()) {
				hand.push_back(i);
				index++;
			}
		}
		std::cout << session.x1.getName()+", your randomly revealed DESTINY is:\n";
		int temp = rand()/RAND_MAX *index;
		std::cout << session.d1.at(hand.at(temp)).printFull();
	}
	else {
		int index = 0;
		for (int i = 0; i < session.d2.size(); i++) {
			if (session.d2.at(i).getIn()) {
				hand.push_back(i);
				index++;
			}
		}
		std::cout << session.x2.getName()+", the randomly revealed DESTINY is:\n";
		int temp = rand()/RAND_MAX * index;
		std::cout << session.d2.at(hand.at(temp)).printFull();
	}
	return;
};

Session SI(Session session, int chooser, std::string destiny) {
	int index = 0;
	int SO = 8;
	std::vector<int> hand;
	if (chooser == 1) {
		int temp = 8;
		if (destiny == "ANY") {
			std::cout << session.x1.getName() + ", choose one DESTINY to swap in:\n";
			for (int i = 0; i < session.d1.size(); i++) {
				if (!session.d1.at(i).getIn()) {
					std::cout << session.d1.at(i).printFull();
					hand.push_back(i);
					index++;
				}
			}
			temp = hand.at(select(index));
			SO = temp;
		}
		else if(destiny=="HEARTBREAKER/HONORABLE EXIT") {
			int available = 0;
			int temp1 = 8;
			int temp2 = 8;
			for (int i = 0; i < session.d1.size(); i++) {
				if (session.d1.at(i).getName() == "HEARTBREAKER" && !session.d1.at(i).getIn()) {
					std::cout << session.d1.at(i).printFull();
					available++;
					temp1 = i;
				}
				if (session.d1.at(i).getName() == "HONORABLE EXIT" && !session.d1.at(i).getIn()) {
					std::cout << session.d1.at(i).printFull();
					available++;
					temp2 = i;
				}
			}
			if (available == 0) {
				std::cout << session.x1.getName() + ", HEARTBREAKER and HONORABLE EXIT are already in your hand. No need to swap.\n";
				return session;
			}
			else if(available==1){
				if (temp2 == 8) {
					temp = temp1;
					SO = temp1;
				}
				else {
					temp = temp2;
					SO = temp2;
				}
			}
			else {
				hand.push_back(temp1);
				hand.push_back(temp2);
				temp = hand.at(select(2));
				SO = temp;
			}
			
		}
		else {
			for (int i = 0; i < session.d1.size(); i++) {
				if (session.d1.at(i).getName() == destiny && !session.d1.at(i).getIn()) {
					std::cout << session.d1.at(i).printFull();
					temp = i;
					SO = i;
					break;
				}
			}
			if (temp == 8) {
				std::cout << session.x1.getName() + ", "+destiny + " is already in your hand. No need to swap.\n";
				return session;
			}
		}
		hand.clear();
		index = 0;
		std::cout << session.x1.getName() + ", choose one DESTINY to swap out:\n";
		for (int i = 0; i < session.d1.size(); i++) {
			if (session.d1.at(i).getIn()) {
				std::cout << session.d1.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}
		
		
		session.d1.at(SO).changeIn();
		temp = select(index);
		session.d1.at(hand.at(temp)).changeIn();
		
	}
	else {
		int temp = 8;
		if (destiny == "ANY") {
			std::cout << session.x2.getName() + ", choose one DESTINY to swap in:\n";
			for (int i = 0; i < session.d2.size(); i++) {
				if (!session.d2.at(i).getIn()) {
					std::cout << session.d2.at(i).printFull();
					hand.push_back(i);
					index++;
				}
			}
			temp = select(index);
			SO = hand.at(temp);
			
		}
		else if (destiny == "HEARTBREAKER/HONORABLE EXIT") {
			int available = 0;
			int temp1 = 8;
			int temp2 = 8;
			for (int i = 0; i < session.d2.size(); i++) {
				if (session.d2.at(i).getName() == "HEARTBREAKER" && !session.d2.at(i).getIn()) {
					std::cout << session.d2.at(i).printFull();
					available++;
					temp1 = i;
				}
				if (session.d2.at(i).getName() == "HONORABLE EXIT" && !session.d2.at(i).getIn()) {
					std::cout << session.d2.at(i).printFull();
					available++;
					temp2 = i;
				}
			}
			if (available == 0) {
				std::cout << session.x2.getName() + ", HEARTBREAKER and HONORABLE EXIT are already in your hand. No need to swap.\n";
				return session;
			}
			else if (available == 1) {
				if (temp2 == 8) {
					temp = temp1;
					SO = temp1;
				}
				else {
					temp = temp2;
					SO = temp2;
				}
			}
			else {
				hand.push_back(temp1);
				hand.push_back(temp2);
				temp = hand.at(select(2));
				SO = temp;
			}

		}
		else {
			for (int i = 0; i < session.d2.size(); i++) {
				if (session.d2.at(i).getName() == destiny && !session.d2.at(i).getIn()) {
					std::cout << session.d2.at(i).printFull();
					temp = i;
					SO = i;
					break;
				}
			}
			if (temp == 8) { 
				std::cout << session.x1.getName() + ", "+destiny + " is already in your hand. No need to swap.\n";
				return session; }
		}
		hand.clear();
		index = 0;
		std::cout << session.x2.getName() + ", choose one DESTINY to swap out:\n";
		for (int i = 0; i < session.d2.size(); i++) {
			if (session.d2.at(i).getIn()) {
				std::cout << session.d2.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}
		session.d2.at(SO).changeIn();
		temp = select(index);
		session.d2.at(hand.at(temp)).changeIn();
		
	}
	return session;
};

Session SO(Session session, int chooser, std::string destiny) {
	int index = 0;
	std::vector<int> hand;
	int temp = 8;
	int SO = 8;
	if (chooser == 1) {
		std::cout << session.x1.getName() + " has the following DESTINIES in hand:\n";
		for (int i = 0; i < session.d1.size(); i++) {
			if (session.d1.at(i).getName() == destiny && session.d1.at(i).getIn()) {
				std::cout << session.d1.at(i).printFull();
				temp = i;
				SO = i;
				break;
			}
		}
		if (temp == 8) {
			std::cout << session.x1.getName() + ", " + destiny + " is not in your hand. No need to swap.\n";
			return session;
		}
		std::cout << session.x1.getName() + ", choose one DESTINY to swap in:\n";
		for (int i = 0; i < session.d1.size(); i++) {
			if (!session.d1.at(i).getIn()) {
				std::cout << session.d1.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}


		session.d1.at(SO).changeIn();
		temp = select(index);
		session.d1.at(hand.at(temp)).changeIn();
	}
	else {
		std::cout << session.x2.getName() + " has the following DESTINIES in hand:\n";
		for (int i = 0; i < session.d2.size(); i++) {
			if (session.d2.at(i).getName() == destiny && session.d2.at(i).getIn()) {
				std::cout << session.d2.at(i).printFull();
				temp = i;
				SO = i;
				break;
			}
		}
		if (temp == 8) {
			std::cout << session.x2.getName() + ", "+destiny + " is not in your hand. No need to swap.\n";
			return session;
		}
		std::cout << session.x2.getName() + ", choose one DESTINY to swap in:\n";
		for (int i = 0; i < session.d2.size(); i++) {
			if (!session.d2.at(i).getIn()) {
				std::cout << session.d2.at(i).printFull();
				hand.push_back(i);
				index++;
			}
		}


		session.d2.at(SO).changeIn();
		temp = select(index);
		session.d2.at(hand.at(temp)).changeIn();
	}
	return session;
};

Session DD(Session session, int player, std::string destiny) {
	int index = 0;
	if (player == 1) {
		std::vector<int> hand;
		if (destiny == "ANY") {
			std::cout << session.x1.getName() + " has the following DESTINIES in hand:\n";
			
			for (int i = 0; i < session.d1.size(); i++) {
				if (session.d1.at(i).getIn()) {
					std::cout << session.d1.at(i).printFull();
					hand.push_back(i);
					index++;
				}
			}
			if (hand.size() == 2) {
				std::cout << "You only have 2 DESTINIES in hand. You cannot discard a DESTINY now.\n";
				return session;
			}
			std::cout << session.x1.getName() + ", select a DESTINY to discard:\n";
			int temp = select(index);
			session.d1.at(hand.at(temp)).changeIn();
			return session;
		}
		else {
			for (int i = 0; i < session.d1.size(); i++) {
				if (session.d1.at(i).getName() == destiny && session.d1.at(i).getIn()) {
					session.d1.at(i).changeIn();
					return session;
				}
				if (session.d1.at(i).getIn()) {
					hand.push_back(i);
				}
			}
			if (hand.size() == 2) {
				std::cout << "You only have 2 DESTINIES in hand. You cannot discard a DESTINY now.\n";
				return session;
			}
			std::cout << session.x1.getName() + ", " + destiny + " is not in your hand. No need to discard.\n";
			return session;
		}
	}
	else {
		std::vector<int> hand;
		if (destiny == "ANY") {
			std::cout << session.x2.getName() + " has the following DESTINIES in hand:\n";
			
			for (int i = 0; i < session.d2.size(); i++) {
				if (session.d2.at(i).getIn()) {
					std::cout << session.d2.at(i).printFull();
					hand.push_back(i);
					index++;
				}
			}
			if (hand.size() == 2) {
				std::cout << "You only have 2 DESTINIES in hand. You cannot discard a DESTINY now.\n";
				return session;
			}
			std::cout << session.x2.getName() + ", select a DESTINY to discard:\n";
			int temp = select(index);
			session.d2.at(hand.at(temp)).changeIn();
			return session;
		}
		else {
			for (int i = 0; i < session.d2.size(); i++) {
				if (session.d2.at(i).getName() == destiny && session.d2.at(i).getIn()) {
					session.d2.at(i).changeIn();
					return session;
				}
				if (session.d2.at(i).getIn()) {
					hand.push_back(i);
				}
			}
			if (hand.size() == 2) {
				std::cout << "You only have 2 DESTINIES in hand. You cannot discard a DESTINY now.\n";
				return session;
			}
			std::cout << session.x2.getName() + ", "+destiny + " is not in your hand. No need to discard.\n";
			return session;
		}
	}
	return session;
};

Session RE(Session session, int chooser, std::string destiny) {
	int index = 0;
	if (chooser == 1) {
		std::cout << session.x1.getName() + " does not have the following DESTINIES in hand:\n";
		if (destiny == "ANY") {
			std::vector<int> hand;
			for (int i = 0; i < session.d1.size(); i++) {
				if (!session.d1.at(i).getIn()) {
					std::cout << session.d1.at(i).printFull();
					hand.push_back(i);
					index++;
				}
			}
			if (index == 0) {
				std::cout << session.x1.getName()+" already has all DESTINY in hand.\n";
				return session;
			}
			else {
				std::cout << session.x1.getName() + ", select a DESTINY to retrieve:\n";
				int temp = select(index);
				session.d1.at(hand.at(temp)).changeIn();
				return session;
			}
			
		}
		else {
			for (int i = 0; i < session.d1.size(); i++) {
				if (session.d1.at(i).getName() == destiny && !session.d1.at(i).getIn()) {
					session.d1.at(i).changeIn();
					return session;
				}
			}
			std::cout << session.x1.getName() + ", "+destiny + " is in your hand. No need to retrieve.\n";
			return session;
		}
	}
	else {
		std::cout << session.x2.getName() + " does not have the following DESTINIES in hand:\n";
		if (destiny == "ANY") {
			std::vector<int> hand;
			for (int i = 0; i < session.d2.size(); i++) {
				if (!session.d2.at(i).getIn()) {
					std::cout << session.d2.at(i).printFull();
					hand.push_back(i);
					index++;
				}
			}
			if (index == 0) {
				std::cout << session.x2.getName() + " already has all DESTINY in hand.\n";
				return session;
			}
			else {
				std::cout << session.x2.getName() + ", select a DESTINY to retrieve:\n";
				int temp = select(index);
				session.d2.at(hand.at(temp)).changeIn();
				return session;
			}
		}
		else {
			for (int i = 0; i < session.d2.size(); i++) {
				if (session.d2.at(i).getName() == destiny && !session.d2.at(i).getIn()) {
					session.d2.at(i).changeIn();
					return session;
				}
			}
			std::cout << session.x2.getName() + ", "+destiny + " is in your hand. No need to retrieve.\n";
			return session;
		}
	}
	return session;
};

Session CO(Session session, int chooser) {
	if (chooser == 1) {
		std::cout << session.x1.getName() + " , please select 1 out of the 3 occupations you receive below.\n";
		std::vector<Occupation> occus1 = { session.occu.at(0), session.occu.at(1), session.occu.at(2) };
		session.occu.erase(session.occu.begin(), session.occu.begin() + 3);
		for (int i = 0; i < 3; i++) {
			std::cout << occus1.at(i).printFull();
		}
		int c1 = select(3);
		session = CancelEffect(session, 1, session.occu1.getDim(), session.occu1.getNum());
		
		session.occu1 = occus1.at(c1);
		session = ApplyEffect(session, 1, session.occu1.getDim(), session.occu1.getNum());
		occus1.erase(occus1.begin() + c1);
		session.occu.push_back(occus1.at(0));
		session.occu.push_back(occus1.at(1));
	}
	else {
		std::cout << session.x2.getName()+" , please select 1 out of the 3 occupations you receive below.\n";
		std::vector<Occupation> occus1 = { session.occu.at(0), session.occu.at(1), session.occu.at(2) };
		session.occu.erase(session.occu.begin(), session.occu.begin() + 3);
		for (int i = 0; i < 3; i++) {
			std::cout << occus1.at(i).printFull();
		}
		int c1 = select(3);
		session = CancelEffect(session, 2, session.occu2.getDim(), session.occu2.getNum());
		session.occu2 = occus1.at(c1);
		session = ApplyEffect(session, 2, session.occu2.getDim(), session.occu2.getNum());
		occus1.erase(occus1.begin() + c1);
		session.occu.push_back(occus1.at(0));
		session.occu.push_back(occus1.at(1));
	}
	return session;
};

Session SWO(Session session) {
	Occupation temp = session.occu1;
	session = CancelEffect(session, 1, session.occu1.getDim(), session.occu1.getDim());
	session = CancelEffect(session, 2, session.occu2.getDim(), session.occu2.getNum());
	session.occu1 = session.occu2;
	session.occu2 = temp;
	session = ApplyEffect(session, 1, session.occu1.getDim(), session.occu1.getDim());
	session = ApplyEffect(session, 2, session.occu2.getDim(), session.occu2.getNum());
	return session;
};

Session CTT(Session session, int chooser) {
	if (chooser == 1) {
		std::cout << session.x1.getName() + ", please discard 1 out of the 3 traits you have.\n";
		std::cout << "1 = "+session.traits1.at(0).getName() + "\n2 = "+session.traits1.at(1).getName()+"\n3 = "+session.traits1.at(2).getName()+"\n";
		int temp = select(3);
		session.traits1.erase(session.traits1.begin() + temp);
		std::cout << session.x1.getName() + " , please select 1 out of the 3 traits you receive below.\n";
		std::vector<Trait> trait1 = { session.traits.at(0), session.traits.at(1), session.traits.at(2) };
		session.traits.erase(session.traits.begin(), session.traits.begin() + 3);
		for (int i = 0; i < 3; i++) {
			std::cout << trait1.at(i).printFull();
		}
		temp = select(3);
		session.traits1.push_back(trait1.at(temp));
		
		trait1.erase(trait1.begin() + temp);
		session.traits.push_back(trait1.at(0));
		session.traits.push_back(trait1.at(1));
	}
	else {
		std::cout << session.x2.getName() + ", please discard 1 out of the 3 traits you have.\n";
		std::cout << "1 = " + session.traits2.at(0).getName() + "\n2 = " + session.traits2.at(1).getName() + "\n3 = " + session.traits2.at(2).getName() + "\n";
		int temp = select(3);
		session.traits2.erase(session.traits2.begin() + temp);
		std::cout << session.x2.getName() + " , please select 1 out of the 3 traits you receive below.\n";
		std::vector<Trait> trait2 = { session.traits.at(0), session.traits.at(1), session.traits.at(2) };
		session.traits.erase(session.traits.begin(), session.traits.begin() + 3);
		for (int i = 0; i < 3; i++) {
			std::cout << trait2.at(i).printFull();
		}
		temp = select(3);
		session.traits2.push_back(trait2.at(temp));

		trait2.erase(trait2.begin() + temp);
		session.traits.push_back(trait2.at(0));
		session.traits.push_back(trait2.at(1));
	}
	return session;
};

Session CRT(Session session, int chooser) {
	if (chooser == 1) {
		int temp = rand() / RAND_MAX * 3;
		std::cout << session.x1.getName() + ", the randomly discarded trait is " + session.traits1.at(temp).getName()+"\n";
		session.traits1.erase(session.traits1.begin() + temp);
		temp = rand() / RAND_MAX * 3;
		session.traits1.push_back(session.traits.at(temp));
		std::cout << session.x1.getName() + ", the randomly chosen trait is " + session.traits1.at(2).getName()+"\n";
		session.traits.erase(session.traits.begin() + temp);
	}
	else {
		int temp = rand() / RAND_MAX * 3;
		std::cout << session.x2.getName() + ", the randomly discarded trait is " + session.traits2.at(temp).getName()+"\n";
		session.traits2.erase(session.traits2.begin() + temp);
		temp = rand() / RAND_MAX * 3;
		session.traits2.push_back(session.traits.at(temp));
		std::cout << session.x2.getName() + ", the randomly chosen trait is " + session.traits2.at(2).getName()+"\n";
		session.traits.erase(session.traits.begin() + temp);
	}
	return session;
};

Session DS(Session session, int chooser, std::string number) {
	int num = std::stoi(number);
	if (chooser == 1) {
		std::cout << session.x1.getName()+", discard a scene. \n";
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < session.hand1.size(); j++) {
				std::cout << std::to_string(j + 1) + " = " + session.hand1.at(j).getTitle() + "\n";
			}
			int temp = select(session.hand1.size());
			session.hand1.erase(session.hand1.begin() + temp);
		}
	}
	else {
		std::cout << session.x2.getName() + ", discard a scene. \n";
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < session.hand2.size(); j++) {
				std::cout << std::to_string(j + 1) + " = " + session.hand2.at(j).getTitle() + "\n";
			}
			int temp = select(session.hand2.size());
			session.hand2.erase(session.hand2.begin() + temp);
		}
	}
	return session;
};

Session TRADE(Session session) {
	std::cout << session.x1.getName() + " has the following SCENES in hand:\n";
	for (int i = 0; i < session.hand1.size(); i++) {
		std::cout << session.hand1.at(i).getTitle()+"\n";
	}
	std::cout << "Select a SCENE to give to " + session.x2.getName() + ":\n";
	int t1 = select(session.hand1.size());

	std::cout << session.x2.getName() + " has the following SCENES in hand:\n";
	for (int i = 0; i < session.hand2.size(); i++) {
		std::cout << session.hand2.at(i).getTitle() + "\n";
	}
	std::cout << "Select a SCENE to give to " + session.x1.getName()+":\n";
	int t2 = select(session.hand2.size());
	session.hand1.push_back(session.hand2.at(t2));
	session.hand2.push_back(session.hand1.at(t1));
	session.hand1.erase(session.hand1.begin() + t1);
	session.hand2.erase(session.hand2.begin() + t2);
	return session;
};

void STELLL(Session session, int chooser) {
	if (chooser == 1) {
		if (session.secret1.size() > 0) {
			std::cout << session.x1.getName() + ", the randomly selected SECRET is:\n";
			int temp = rand() / RAND_MAX * session.secret1.size();
			std::cout << session.secret1.at(temp).getTitle();
			std::cout << "\nTell " + session.x2.getName() + " whether you think it is beneficial for them to reveal it or not. \n1 = Yes\n2 = No\n";
			int choice = select(2);

		}
	}
	else {
		if (session.secret2.size() > 0) {
			std::cout << session.x2.getName() + ", the randomly selected SECRET is:\n";
			int temp = rand() / RAND_MAX * session.secret2.size();
			std::cout << session.secret2.at(temp).getTitle();
			std::cout << "\nTell " + session.x1.getName() + " whether you think it is beneficial for them to reveal it or not. \n1 = Yes\n2 = No\n";
			int choice = select(2);

		}
	}
	
	
	return;
};

Session DRC(Session session, int player) {
	if (player == 1) {
		std::cout << session.x1.getName() + ", the randomly discarded SCENE is:\n";
		int temp = rand() / RAND_MAX * session.hand1.size();
		std::cout << session.hand1.at(temp).getTitle();
		session.hand1.erase(session.hand1.begin() + temp);
	}
	else {
		std::cout << session.x2.getName() + ", the randomly discarded SCENE is:\n";
		int temp = rand() / RAND_MAX * session.hand2.size();
		std::cout << session.hand2.at(temp).getTitle();
		session.hand2.erase(session.hand2.begin() + temp);
	}
	return session;
};