#pragma once
#include "Enums.h"
#include "Scene.h"
#include "Feature.h"
#include "Occupation.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

// take from http://stackoverflow.com/a/236803/248823
void split(const std::string& s, char delim, std::vector<std::string>& elems);

std::map<std::string, std::string> importVocab();

std::vector<Feature> importFeatures();
std::vector<Occupation> importOccus();



std::vector<Chapter> importChapters();

std::vector<Scene> importScenes();
Scene generateScene(std::vector<std::string> info);

std::vector<Scene> importEffects(std::vector<Scene> scenes);
/*
M = Match
MC = Match C
ME = Match different
CXX = Choose X and X
CD-AB = One choose D, the other A or B
CDE = One choose D, the other didn't
E = else
B = Both
PA = Partner
NM = No match
D = discard (destiny)
N = not
PM = Personality token (length 2 +F)
T = tell (length 2)
DR = draw (scene) (length 3)
CH = chooser (satisfaction change)
OT = other (satisfaction change)
RD = reveal and then discard (destiny)
PL = player (satisfaction change)
RI = reveal if (certain destiny)
RE = retrive (a destiny)
R = reveal (a destiny)
DS = discard scene
SI = swap in
ANY = any (destiny)
STELL = card 22 (see a secret without reveal)
CO = change occupation
SWO = switch occupation with partner
CT = change a trait
TRADE = trade a scene
RS = reveal a secret in play played by the OTHER
*/