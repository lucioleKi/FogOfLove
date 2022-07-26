#pragma once
#include "Enums.h"
#include "Session.h"
#include "CharacterInitial.h"
#include "Trait.h"
#include "Occupation.h"
#include "Feature.h"
#include "PersonalityToken.h"
#include "SynopsisDestiny.h"
#include "Shuffle.h"
#include "ReadTxt.h"
#include <vector>
#include <limits>
#include <string>
#include <iostream>




int startGame();

Session startSession();
Session runGame(Session session);

Session specialOp(Session session, int index, Deck deck, int turn, Scene scene);

Session resolution(Session session);
