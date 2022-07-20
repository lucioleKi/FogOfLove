#pragma once
enum PersonalityDim {
	Discipline,
	Curiosity,
	Extroversion,
	Sensitivity,
	Gentleness,
	Sincerity,

};

enum TraitGoalType {
	Individual,
	Shared,
};

enum Gender {
	Female,
	Male,
	Other,
};

enum Deck {
	Sweet,
	Serious,
	Drama,
};

enum Instruction {
	change = 0x00,
	reveal = 0x01,
	draw = 0x02,
	discard = 0x03,
	tell = 0x04,
	swapIn = 0x05,
	swapOut = 0x06,
	trade = 0x07,
	alter = 0x08,
	ignore = 0x09,
	doubleImpact = 0x0a,
	guess = 0x0b,
};


