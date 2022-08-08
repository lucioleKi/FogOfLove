#include "PersonalityToken.h"
#include "Occupation.h"
#include "Feature.h"
#include <string>
#include <vector>
#include <iostream>



void PersonalityToken::change(int arr, int position, int num) {
	personalityShared.at(position) = personalityShared.at(position) + num;
	switch (arr) {
	case 1:
		personality1.at(position) = personality1.at(position) + num;
		return;
	case 2:
		personality2.at(position) = personality2.at(position) + num;
		return;
	}
	
};

void PersonalityToken::changeOccu(int player, Occupation occu) {
	switch (occu.getDim())
	{
	case Discipline:
		switch (player)
		{
		case 1:
			if (occu.getNum() > 0) {
				personality1.at(0)++;
				personalityShared.at(0)++;
			}
			else {
				personality1.at(1)++;
				personalityShared.at(1)++;
			}
			break;
		case 2:
			if (occu.getNum() > 0) {
				personality2.at(0)++;
				personalityShared.at(0)++;
			}
			else {
				personality2.at(1)++;
				personalityShared.at(1)++;
			}
			break;
		}
		break;
	case Curiosity:
		switch (player)
		{
		case 1:
			if (occu.getNum() > 0) {
				personality1.at(2)++;
				personalityShared.at(2)++;
			}
			else {
				personality1.at(3)++;
				personalityShared.at(3)++;
			}
			break;
		case 2:
			if (occu.getNum() > 0) {
				personality2.at(2)++;
				personalityShared.at(2)++;
			}
			else {
				personality2.at(3)++;
				personalityShared.at(3)++;
			}
			break;
		}
		break;
	case Extroversion:
		switch (player)
		{
		case 1:
			if (occu.getNum() > 0) {
				personality1.at(4)++;
				personalityShared.at(4)++;
			}
			else {
				personality1.at(5)++;
				personalityShared.at(5)++;
			}
			break;
		case 2:
			if (occu.getNum() > 0) {
				personality2.at(4)++;
				personalityShared.at(4)++;
			}
			else {
				personality2.at(5)++;
				personalityShared.at(5)++;
			}
			break;
		}
		break;
	case Sensitivity:
		switch (player)
		{
		case 1:
			if (occu.getNum() > 0) {
				personality1.at(6)++;
				personalityShared.at(6)++;
			}
			else {
				personality1.at(7)++;
				personalityShared.at(7)++;
			}
			break;
		case 2:
			if (occu.getNum() > 0) {
				personality2.at(6)++;
				personalityShared.at(6)++;
			}
			else {
				personality2.at(7)++;
				personalityShared.at(7)++;
			}
			break;
		}
		break;
	case Gentleness:
		switch (player)
		{
		case 1:
			if (occu.getNum() > 0) {
				personality1.at(8)++;
				personalityShared.at(8)++;
			}
			else {
				personality1.at(9)++;
				personalityShared.at(9)++;
			}
			break;
		case 2:
			if (occu.getNum() > 0) {
				personality2.at(8)++;
				personalityShared.at(8)++;
			}
			else {
				personality2.at(9)++;
				personalityShared[9]++;
			}
			break;
		}
		break;
	case Sincerity:
		switch (player)
		{
		case 1:
			if (occu.getNum() > 0) {
				personality1.at(10)++;
				personalityShared.at(10)++;
			}
			else {
				personality1.at(11)++;
				personalityShared.at(11)++;
			}
			break;
		case 2:
			if (occu.getNum() > 0) {
				personality2.at(10)++;
				personalityShared.at(10)++;
			}
			else {
				personality2.at(11)++;
				personalityShared.at(11)++;
			}
			break;
		}
		break;
	}
};

void PersonalityToken::changeFeature(int player, Feature fea) {
	switch (fea.getDim())
	{
	case Discipline:
		switch (player)
		{
		case 1:
			if (fea.getNum() > 0) {
				personality1.at(0)++;
				personalityShared.at(0)++;
			}
			else {
				personality1.at(1)++;
				personalityShared.at(1)++;
			}
			break;
		case 2:
			if (fea.getNum() > 0) {
				personality2.at(0)++;
				personalityShared.at(0)++;
			}
			else {
				personality2.at(1)++;
				personalityShared.at(1)++;
			}
			break;
		}
		break;
	case Curiosity:
		switch (player)
		{
		case 1:
			if (fea.getNum() > 0) {
				personality1.at(2)++;
				personalityShared.at(2)++;
			}
			else {
				personality1.at(3)++;
				personalityShared.at(3)++;
			}
			break;
		case 2:
			if (fea.getNum() > 0) {
				personality2.at(2)++;
				personalityShared.at(2)++;
			}
			else {
				personality2.at(3)++;
				personalityShared.at(3)++;
			}
			break;
		}
		break;
	case Extroversion:
		switch (player)
		{
		case 1:
			if (fea.getNum() > 0) {
				personality1.at(4)++;
				personalityShared.at(4)++;
			}
			else {
				personality1.at(5)++;
				personalityShared.at(5)++;
			}
			break;
		case 2:
			if (fea.getNum() > 0) {
				personality2.at(4)++;
				personalityShared.at(4)++;
			}
			else {
				personality2.at(5)++;
				personalityShared.at(5)++;
			}
			break;
		}
		break;
	case Sensitivity:
		switch (player)
		{
		case 1:
			if (fea.getNum() > 0) {
				personality1.at(6)++;
				personalityShared.at(6)++;
			}
			else {
				personality1.at(7)++;
				personalityShared.at(7)++;
			}
			break;
		case 2:
			if (fea.getNum() > 0) {
				personality2.at(6)++;
				personalityShared.at(6)++;
			}
			else {
				personality2.at(7)++;
				personalityShared.at(7)++;
			}
			break;
		}
		break;
	case Gentleness:
		switch (player)
		{
		case 1:
			if (fea.getNum() > 0) {
				personality1.at(8)++;
				personalityShared.at(8)++;
			}
			else {
				personality1.at(9)++;
				personalityShared.at(9)++;
			}
			break;
		case 2:
			if (fea.getNum() > 0) {
				personality2.at(8)++;
				personalityShared.at(8)++;
			}
			else {
				personality2.at(9)++;
				personalityShared.at(9)++;
			}
			break;
		}
		break;
	case Sincerity:
		switch (player)
		{
		case 1:
			if (fea.getNum() > 0) {
				personality1.at(10)++;
				personalityShared.at(10)++;
			}
			else {
				personality1.at(11)++;
				personalityShared.at(11)++;
			}
			break;
		case 2:
			if (fea.getNum() > 0) {
				personality2.at(10)++;
				personalityShared.at(10)++;
			}
			else {
				personality2.at(11)++;
				personalityShared.at(11)++;
			}
			break;
		}
		break;
	}
};

std::string PersonalityToken::printFull() {
	std::string x{"Player 1: \n"};
	for (int i = 0; i < 6; i++) {
		x = x + text.at(i) + ": + " + std::to_string(personality1.at(i * 2)) + " - " + std::to_string(personality1.at(i * 2+1)) + ". ";
		if (i == 2) {
			x = x + "\n";
		}
	}
	x = x + "\nPlayer2: \n";
	for (int i = 0; i < 6; i++) {
		x = x + text.at(i) + ": + " + std::to_string(personality2.at(i * 2)) + " - " + std::to_string(personality2.at(i * 2+1)) + ". ";
		if (i == 2) {
			x = x + "\n";
		}
	}
	x = x + "\nShared: \n";
	for (int i = 0; i < 6; i++) {
		x = x + text.at(i) + ": + " + std::to_string(personalityShared.at(i * 2)) + " - " + std::to_string(personalityShared.at(i * 2+1)) + ". ";
		if (i == 2) {
			x = x + "\n";
		}
	}
	x = x + "\n";
	return x;
};