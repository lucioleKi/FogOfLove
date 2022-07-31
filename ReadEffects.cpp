#include "Enums.h"
#include "Scene.h"
#include "ReadEffects.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

Scene readEffects(Scene s, std::vector<std::string> effects) {

	int numChoice = s.getChoices().size();
	int numF = std::count(effects.begin(), effects.end(), "F");
	int index = 1;
	
	std::vector<Choice> tempC;

	if (s.getWho() == 'S') {
		std::vector<std::string> code;
		Choice c = s.getChoices().at(0);
		while (effects.at(index) != "F") {
			code.push_back(effects.at(index));
			index++;
		}
		c.setCode(code);
		tempC.push_back(c);
		for (int i = 1; i < s.getChoices().size(); i++) {
			tempC.push_back(s.getChoices().at(i));
		}
		s.setChoices(tempC);
	}
	else if (s.getWho() == 'T') {
		//make 2 additional objects, not-revealed, if-revealed respectively
		std::vector<Additional> a;
		for (int i = 0; i < 2; i++) {
			//additional effects

			std::vector<std::string> code{};
			while (effects.at(index) != "F") {
				code.push_back(effects.at(index));
				index++;
			}
			Additional add{ code };
			add.setFull("");
			a.push_back(add);
			index++;
		}

		s.setAddis(a);
	}
	else if (s.getWho() == 'C') {
		//make 2 aditional objects, for initial and not-revealed
		std::vector<Additional> a;
		std::vector<std::string> code{};
		while (effects.at(index) != "F") {
				code.push_back(effects.at(index));
				index++;
			}
		Additional add{ code };
		add.setFull("");
		a.push_back(add);
		index++;
		s.setAddis(a);

		//choice effects
		for (int i = 0; i < numChoice; i++) {
			int begin = index;
			std::vector<std::string> code;
			Choice c = s.getChoices().at(i);
			while (effects.at(index) != "F") {
				index++;
			}
			PT pt = readPT(begin, index, c, effects);
			c = pt.c;
			effects = pt.effects;

			index = index - pt.in + 1;
			tempC.push_back(c);
			
		}
		s.setChoices(tempC);

	}
	else if (s.getWho() == 'B' || s.getWho() == 'P') {
		for (int i = 0; i < numChoice; i++) {
			//choice effects
			int begin = index;
			std::vector<std::string> code;
			Choice c = s.getChoices().at(i);
			while (effects.at(index) != "F") {

				index++;
			}
			//c.setCode(code);
			//handle PT here

			PT pt = readPT(begin, index, c, effects);
			c = pt.c;
			effects = pt.effects;

			index = index - pt.in + 1;
			tempC.push_back(c);
			//handle choser and other here
			/*PT choser = readChoser(begin, index, c, effects);
			effects = choser.effects;
			c = choser.c;

			index = index - choser.in;
			*/
			//std::cout << "index out"+std::to_string(index) + "\n";
		}
		s.setChoices(tempC);
		std::vector<Additional> a;
		for (int i = 0; i < numF - numChoice; i++) {
			//additional effects

			std::vector<std::string> code{};
			while (effects.at(index) != "F") {
				code.push_back(effects.at(index));
				index++;
			}
			Additional add{ code };
			add.setFull("");
			a.push_back(add);
			index++;
		}

		s.setAddis(a);
	}
	
	
	//std::cout<<s.printFull();
	return s;
};

Chapter readEffectsC(Chapter s, std::vector<std::string> effects) {
	int numChoice = s.getChoices().size();
	int numF = std::count(effects.begin(), effects.end(), "F");
	int index = 1;

	std::vector<Choice> tempC;
	for (int i = 0; i < numChoice; i++) {
		//choice effects
		int begin = index;
		std::vector<std::string> code;
		Choice c = s.getChoices().at(i);
		while (effects.at(index) != "F") {

			index++;
		}
		//c.setCode(code);
		//handle PT here
		PT pt = readPT(begin, index, c, effects);
		c = pt.c;
		effects = pt.effects;

		index = index - pt.in + 1;
		tempC.push_back(c);
	}
	s.setChoices(tempC);
	std::vector<Additional> a;
	for (int i = 0; i < numF - numChoice; i++) {
		//additional effects

		std::vector<std::string> code{};
		while (effects.at(index) != "F") {
			code.push_back(effects.at(index));
			index++;
		}
		Additional add{ code };
		add.setFull("");
		a.push_back(add);
		index++;
	}

	s.setAddis(a);
	//std::cout<<s.printFull();
	return s;
}


PT readPT(int begin,int end,  Choice c, std::vector<std::string> effects) {
	int numPT = std::count(effects.begin()+begin, effects.begin()+end, "PT");
	int index = begin;

	std::vector<PersonalityDim> dims;
	std::array<int, 3> nums{0, 0, 0};
	for (int i = 0; i < numPT; i++) {
		if (effects.at(index) == "F") { break; };
		while (effects.at(index) != "PT") {
			index++;
		}

		int temp = std::stoi(effects.at(index+1));
		PersonalityDim dim = (PersonalityDim)temp;
		int num = std::stoi(effects.at(index + 2));
		dims.push_back(dim);
		nums.at(i) = num;
		effects.erase(effects.begin()+index, effects.begin()+index+3);
		//std::cout << "index in " + std::to_string(index)+"\n";
	}
	if (numPT != 0) {
		c.setDims(dims);
		c.setNums(nums);
	}
	std::vector<std::string> code;
	while (effects.at(begin) != "F") {
		code.push_back(effects.at(begin));
		begin++;
	}
	c.setCode(code);
	return PT{numPT*3, c, effects };
};

/*
PT readChoser(int begin, int index, Choice c, std::vector<std::string> effects) {
	int del = 0;
	std::vector<std::string> code;
	if (effects.at(begin) == "F") { return PT{ 0, c, effects }; };
	if (effects.at(begin) == "CH"||effects.at(begin)=="B") {
		if (effects.at(begin + 1).find_first_of("0123456789") != std::string::npos) {
			int num = std::stoi(effects.at(begin+1));
			c.setChoser(num);
			effects.erase(effects.begin() + begin + 1);
			if (effects.at(begin) == "B") {
				c.setOther(num);
			}
			del = del+1;
		}
		
		
	}
	while (effects.at(begin) != "F" && effects.at(begin) != "OT") {
		code.push_back(effects.at(begin));
		begin++;
	}

	if (effects.at(begin) == "OT") {
		if (effects.at(begin + 1).find_first_of("0123456789") != std::string::npos) {
			int num = std::stoi(effects.at(begin + 1));
			c.setOther(num);
			effects.erase(effects.begin() + begin + 1);
			del = del + 1;
			//std::cout << c.getDescription() + "\n";
			//std::cout << "index in " + std::to_string(c.getOther())+"\n";
		}
	}
	while (effects.at(begin) != "F") {
		code.push_back(effects.at(begin));
		begin++;
	}
	c.setCode(code);
	return PT{ del, c, effects };
};
*/