#pragma once
#include "Enums.h"
#include "Scene.h"
#include "Trait.h"
#include "Occupation.h"
#include "Feature.h"
#include "PersonalityToken.h"
#include "SynopsisDestiny.h"
#include "BeforeScenes.h"
#include "Shuffle.h"
#include "ReadTxt.h"
#include "Session.h"
#include <vector>
#include <string>
#include <iostream>

Session drawStarting(Session game);

Session drawFill(Session session, Deck d);

int chooseScene(Session game, int turn);