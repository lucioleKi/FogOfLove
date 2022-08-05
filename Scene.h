#pragma once
#include "Enums.h"
#include <array>
#include <vector>
#include <string>
#include <iostream>



class Card {
protected:
	std::string title;
	std::string line;
	
public:
	std::string getTitle() { return title; };
	std::string getLine() { return line; };
	void setTitle(std::string t) { title = t; };
	void setLine(std::string l) { line = l; };
};

class Choice {
private:
	std::string description;
	int choser_satis;
	int other_satis;
	std::vector<PersonalityDim> dims;
	std::array<int, 3> nums;
	std::string text;
	std::vector<std::string> code;
public:
	Choice(std::string d) { description = d; };
	void setDescription(std::string d) { description = d; };
	void setChoser(int c) { choser_satis = c; };
	void setOther(int o) { other_satis = o; };
	void setDims(std::vector<PersonalityDim> d) { dims = d; };
	void setNums(std::array<int, 3> n) { nums = n; };
	void setFull(std::string f) { text = f; };
	void setCode(std::vector<std::string> c) { code = c; };
	
	std::string getDescription() { return description; };
	int getChoser() { return choser_satis; };
	int getOther() { return other_satis; };
	std::vector<PersonalityDim> getDims() { return dims; };
	std::array<int, 3> getNums() { return nums; };
	std::string getFull() { return text; };
	std::vector<std::string> getCode() { return code; };
	std::string printFull();
};

class Additional {
private:
	std::vector<std::string> code;
	std::string text;
public:
	Additional(std::vector<std::string> c) { code = c; };
	void setCode(std::vector<std::string> c) { code = c; };
	void setFull(std::string t) { text = t; };
	std::vector<std::string> getCode() { return code; };
	std::string getFull() { return text; };
};

class Chapter : public Card {
private:
	int index;
	
	int length;
	char whoChoose;
	std::vector<Deck> drawFrom;
	std::vector<Choice> choices;
	std::vector<Additional> additionals;
public:
	Chapter(int i, char b, int l, std::vector<Deck> d);
	void setIndex(int i) { index = i; };
	void setWho(char w) { whoChoose = w; };
	void setDraw(std::vector<Deck> d) { drawFrom = d; };
	void setChoices(std::vector<Choice> c) { choices = c; };
	void setAddis(std::vector<Additional> a) { additionals = a; };
	int getIndex() { return index; };
	char getWho() { return whoChoose; };
	int getLength() { return length; };
	std::vector<Deck> getDraw() { return drawFrom; };
	std::vector<Choice> getChoices() { return choices; };
	std::vector<Additional> getAddis() { return additionals; };
	std::string printFull();
};

class Scene: public Card{
private:
	int index;
	std::string explain_choices;
	Deck deck;
	//B = Both choose, P = Partner chooses, S = Situation, E = Special Effect, T = Secret, C = Secret w/ Partner chooses, V = Reveal secret, R = Reaction, N = Reaction w/ Partner chooses
	char whoChoose;
	std::vector<Choice> choices;
	std::vector<Additional> additionals;
public:
	Scene(int i, Deck d, char w);
	void setIndex(int i) { index = i; };
	void setExplain(std::string e) { explain_choices = e; };
	void setWho(char w) { whoChoose = w; };
	void setDeck(Deck d) { deck = d; };
	void setChoices(std::vector<Choice> c) { choices = c; };
	void setAddis(std::vector<Additional> a) { additionals = a; };
	int getIndex() { return index; };
	std::string getExplain() { return explain_choices; };
	char getWho() { return whoChoose; };
	Deck getDeck() { return deck; };
	std::vector<Choice> getChoices() { return choices; };
	std::vector<Additional> getAddis() { return additionals; };
	std::string printFull();
};
