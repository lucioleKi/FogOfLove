#include "PersonalityToken.h"
#include "Occupation.h"
#include "Feature.h"
#include <string>
#include <iostream>

PersonalityToken::PersonalityToken() {
	int personality1[12]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int personality2[12]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int personalityShared[12]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};

void PersonalityToken::change(int arr, int position, int num) {
	personalityShared[position] = personalityShared[position] + num;
	switch (arr) {
	case 1:
		personality1[position] = personality1[position] + num;
		return;
	case 2:
		personality2[position] = personality2[position] + num;
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
				personality1[0]++;
				personalityShared[0]++;
			}
			else {
				personality1[1]++;
				personalityShared[1]++;
			}
			break;
		case 2:
			if (occu.getNum() > 0) {
				personality2[0]++;
				personalityShared[0]++;
			}
			else {
				personality2[1]++;
				personalityShared[1]++;
			}
			break;
		}
		break;
	case Curiosity:
		switch (player)
		{
		case 1:
			if (occu.getNum() > 0) {
				personality1[2]++;
				personalityShared[2]++;
			}
			else {
				personality1[3]++;
				personalityShared[3]++;
			}
			break;
		case 2:
			if (occu.getNum() > 0) {
				personality2[2]++;
				personalityShared[2]++;
			}
			else {
				personality2[3]++;
				personalityShared[3]++;
			}
			break;
		}
		break;
	case Extroversion:
		switch (player)
		{
		case 1:
			if (occu.getNum() > 0) {
				personality1[4]++;
				personalityShared[4]++;
			}
			else {
				personality1[5]++;
				personalityShared[5]++;
			}
			break;
		case 2:
			if (occu.getNum() > 0) {
				personality2[4]++;
				personalityShared[4]++;
			}
			else {
				personality2[5]++;
				personalityShared[5]++;
			}
			break;
		}
		break;
	case Sensitivity:
		switch (player)
		{
		case 1:
			if (occu.getNum() > 0) {
				personality1[6]++;
				personalityShared[6]++;
			}
			else {
				personality1[7]++;
				personalityShared[7]++;
			}
			break;
		case 2:
			if (occu.getNum() > 0) {
				personality2[6]++;
				personalityShared[6]++;
			}
			else {
				personality2[7]++;
				personalityShared[7]++;
			}
			break;
		}
		break;
	case Gentleness:
		switch (player)
		{
		case 1:
			if (occu.getNum() > 0) {
				personality1[8]++;
				personalityShared[8]++;
			}
			else {
				personality1[9]++;
				personalityShared[9]++;
			}
			break;
		case 2:
			if (occu.getNum() > 0) {
				personality2[8]++;
				personalityShared[8]++;
			}
			else {
				personality2[9]++;
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
				personality1[10]++;
				personalityShared[10]++;
			}
			else {
				personality1[11]++;
				personalityShared[11]++;
			}
			break;
		case 2:
			if (occu.getNum() > 0) {
				personality2[10]++;
				personalityShared[10]++;
			}
			else {
				personality2[11]++;
				personalityShared[11]++;
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
				personality1[0]++;
				personalityShared[0]++;
			}
			else {
				personality1[1]++;
				personalityShared[1]++;
			}
			break;
		case 2:
			if (fea.getNum() > 0) {
				personality2[0]++;
				personalityShared[0]++;
			}
			else {
				personality2[1]++;
				personalityShared[1]++;
			}
			break;
		}
		break;
	case Curiosity:
		switch (player)
		{
		case 1:
			if (fea.getNum() > 0) {
				personality1[2]++;
				personalityShared[2]++;
			}
			else {
				personality1[3]++;
				personalityShared[3]++;
			}
			break;
		case 2:
			if (fea.getNum() > 0) {
				personality2[2]++;
				personalityShared[2]++;
			}
			else {
				personality2[3]++;
				personalityShared[3]++;
			}
			break;
		}
		break;
	case Extroversion:
		switch (player)
		{
		case 1:
			if (fea.getNum() > 0) {
				personality1[4]++;
				personalityShared[4]++;
			}
			else {
				personality1[5]++;
				personalityShared[5]++;
			}
			break;
		case 2:
			if (fea.getNum() > 0) {
				personality2[4]++;
				personalityShared[4]++;
			}
			else {
				personality2[5]++;
				personalityShared[5]++;
			}
			break;
		}
		break;
	case Sensitivity:
		switch (player)
		{
		case 1:
			if (fea.getNum() > 0) {
				personality1[6]++;
				personalityShared[6]++;
			}
			else {
				personality1[7]++;
				personalityShared[7]++;
			}
			break;
		case 2:
			if (fea.getNum() > 0) {
				personality2[6]++;
				personalityShared[6]++;
			}
			else {
				personality2[7]++;
				personalityShared[7]++;
			}
			break;
		}
		break;
	case Gentleness:
		switch (player)
		{
		case 1:
			if (fea.getNum() > 0) {
				personality1[8]++;
				personalityShared[8]++;
			}
			else {
				personality1[9]++;
				personalityShared[9]++;
			}
			break;
		case 2:
			if (fea.getNum() > 0) {
				personality2[8]++;
				personalityShared[8]++;
			}
			else {
				personality2[9]++;
				personalityShared[9]++;
			}
			break;
		}
		break;
	case Sincerity:
		switch (player)
		{
		case 1:
			if (fea.getNum() > 0) {
				personality1[10]++;
				personalityShared[10]++;
			}
			else {
				personality1[11]++;
				personalityShared[11]++;
			}
			break;
		case 2:
			if (fea.getNum() > 0) {
				personality2[10]++;
				personalityShared[10]++;
			}
			else {
				personality2[11]++;
				personalityShared[11]++;
			}
			break;
		}
		break;
	}
};