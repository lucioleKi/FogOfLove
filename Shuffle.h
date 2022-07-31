#pragma once

#include <algorithm>
#include <random>
#include <map>
#include <iostream>
#include <conio.h>

template <typename T>
std::vector<T> Shuffle(std::vector<T> x) {
	std::random_device rd;
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(x.begin(), x.end(), rng);
	return x;
};

template<typename T>
struct dealCards {
	T deck{};
	T p1{};
	T p2{};
};

template<typename T>
std::vector<T> Vocab(std::vector<T> x, std::map<std::string, std::string> pairs) {
	/*for (auto itr = pairs.begin(); itr != pairs.end(); ++itr) {
		std::cout << itr->first
			<< '\t' << itr->second << '\n';
	}*/
	
	for (int i = 0; i < x.size(); i++) {
		T temp = x.at(i);
		if (temp.getWho() == 'B' || temp.getWho() == 'P'||temp.getWho()=='C'||temp.getWho()=='T') {
			std::vector<Choice> tempC;
			for (int j = 0; j < x.at(i).getChoices().size(); j++) {
				Choice c = x.at(i).getChoices().at(j);
				for (int k = 0; k < x.at(i).getChoices().at(j).getCode().size(); k++) {
					if (x.at(i).getChoices().at(j).getCode().at(k) != "F") {
						if (x.at(i).getChoices().at(j).getCode().at(k).find_first_of("0123456789") != std::string::npos) {
							if (std::stoi(x.at(i).getChoices().at(j).getCode().at(k)) > 0) {
								//std::cout << std::to_string(std::stoi(x.at(i).getChoices().at(j).getCode().at(k))) + "\n";
								c.setFull(c.getFull() + " + " + std::to_string(std::stoi(c.getCode().at(k))) + ". ");
							}
							else {
								//std::cout << std::to_string(std::stoi(x.at(i).getChoices().at(j).getCode().at(k))) + "\n";
								c.setFull(c.getFull() + " - " + std::to_string(std::stoi(c.getCode().at(k)) * (-1)) + ". ");
							}
						}
						else {
							if (pairs.find(x.at(i).getChoices().at(j).getCode().at(k)) != pairs.end()) {
								std::string s = pairs.find(c.getCode().at(k))->second;
								//std::cout << s+"\n";
								c.setFull(c.getFull() + " " + s);
							}
							else {
								std::cout << "Cant find" + c.getCode().at(k) + "\n";
							}
						}

					}
					else {
						c.setFull(c.getFull() + "\n");
					}

				}
				tempC.push_back(c);
			}
			temp.setChoices(tempC);
			std::vector<Additional> tempA;
			for (int j = 0; j < x.at(i).getAddis().size(); j++) {
				Additional addi = x.at(i).getAddis().at(j);
				for (int k = 0; k < addi.getCode().size(); k++) {
					if (addi.getCode().at(k) != "F") {
						if (addi.getCode().at(k) == "DS") {
							addi.setFull(addi.getFull() + "discard " + addi.getCode().at(k + 1) + " SCENE. ");
							k++;
							continue;
						}
						else if (addi.getCode().at(k) == "RI") {
							addi.setFull(addi.getFull() + "reveal if you have " + addi.getCode().at(k + 1) + " in hand. ");
							k++;
							continue;
						}
						if (x.at(i).getAddis().at(j).getCode().at(k).find_first_of("0123456789") != std::string::npos) {
							if (std::stoi(x.at(i).getAddis().at(j).getCode().at(k)) > 0) {
								//std::cout << std::to_string(std::stoi(x.at(i).getAddis().at(j).getCode().at(k)));
								addi.setFull(addi.getFull() + "+ " + addi.getCode().at(k) + ". ");
							}
							else {
								//std::cout << std::to_string(std::stoi(x.at(i).getAddis().at(j).getCode().at(k)));
								addi.setFull(addi.getFull() + "- " + std::to_string(std::stoi(x.at(i).getAddis().at(j).getCode().at(k)) * (-1)) + ". ");
							}
						}
						else {
							if (pairs.find(x.at(i).getAddis().at(j).getCode().at(k)) != pairs.end()) {
								std::string s = pairs.find(addi.getCode().at(k))->second;
								//std::cout << s + "\n";
								addi.setFull(addi.getFull() + s + " ");
							}
						}
					}
					else {
						addi.setFull(addi.getFull() + "\n");
					}
				}
				tempA.push_back(addi);
			}
			x.at(i).setChoices(tempC);
			x.at(i).setAddis(tempA);
		}
		
		//std::cout<<x.at(i).printFull();
	}
	return x;
};

template<typename T>
T ApplyEffect(T x, int player, PersonalityDim d, int number) {
	if (player == 1) {
		if (number > 0) {
			x.per.change(1, d * 2, number);
		}
		else {
			x.per.change(1, d * 2+1, number*(-1));
		}
	}
	else {
		if (number > 0) {
			x.per.change(2, d * 2, number);
		}
		else {
			x.per.change(2, d * 2+1, number*(-1));
		}
	}
	std::cout<<x.per.printFull();
	return x;
};

template<typename T>
T CancelEffect(T x, int player, PersonalityDim d, int number) {
	if (player == 1) {
		if (number > 0) {
			x.per.change(1, d * 2, number * (-1));
		}
		else {
			x.per.change(1, d * 2+1, number);
		}
	}
	else {
		if (number > 0) {
			x.per.change(2, d * 2, number * (-1));
		}
		else {
			x.per.change(2, d * 2+1, number);
		}
	}
	std::cout << x.per.printFull();
	return x;
};