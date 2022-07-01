#pragma once
#include "Enums.h"
#include "Scene.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// take from http://stackoverflow.com/a/236803/248823
void split(const std::string& s, char delim, std::vector<std::string>& elems);

std::vector<Chapter> importChapters();

std::vector<Scene> importScenes();
Scene generateScene(std::vector<std::string> info);

/*
M = Match
MC = Match C
ME = Match different
CXX = Choose X and X
CD-AB = One choose D, the other A or B
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
R = reveal (a destiny)
DS = discard scene
SI = swap in
ANY = any (destiny)
STELL = card 22 (see a secret without reveal)
*/