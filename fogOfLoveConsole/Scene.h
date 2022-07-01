#pragma once
#include "Enums.h"
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
	//int choser_satis;
	//int other_satis;
	//std::vector<PersonalityDim> dims;
	//int num[2];
public:
	Choice(std::string d) { description = d; };
	void setDescription(std::string d) { description = d; };
	std::string getDescription() { return description; };
};

class Additional {
	std::string match;
	std::string noMatch;
	
};

class Chapter : public Card {
private:
	int index;
	bool both;
	int length;
	std::vector<Deck> drawFrom;
	std::vector<Choice> choices;
public:
	Chapter(int i, bool b, int l, std::vector<Deck> d);
	void setIndex(int i) { index = i; };
	void setBoth(bool b) { both = b; };
	void setDraw(std::vector<Deck> d) { drawFrom = d; };
	void setChoices(std::vector<Choice> c) { choices = c; };
	int getIndex() { return index; };
	bool getBoth() { return both; };
	int getLength() { return length; };
	std::vector<Deck> getDraw() { return drawFrom; };
	std::vector<Choice> getChoices() { return choices; };
	std::string printFull();
};

class Scene: public Card{
private:
	int index;
	std::string explain_choices;
	Deck deck;
	char whoChoose;
	std::vector<Choice> choices;
public:
	Scene(int i, Deck d, char w);
	void setIndex(int i) { index = i; };
	void setExplain(std::string e) { explain_choices = e; };
	void setWho(char w) { whoChoose = w; };
	void setDeck(Deck d) { deck = d; };
	void setChoices(std::vector<Choice> c) { choices = c; };
	int getIndex() { return index; };
	std::string getExplain() { return explain_choices; };
	char getWho() { return whoChoose; };
	Deck getDeck() { return deck; };
	std::vector<Choice> getChoices() { return choices; };
	std::string printFull();
};

//to-do functions
std::vector<Chapter> selectChapters();
std::vector<Scene> selectScenes();
