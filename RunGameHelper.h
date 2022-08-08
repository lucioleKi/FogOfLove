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
#include "ResolveEffects.h"
#include "VocabTranslator.h"
#include <vector>
#include <string>
#include <iostream>

Session specialOp(Session session, int index, Deck deck, int turn, Scene scene);

Session drawStarting(Session game);

Session drawFill(Session session, Deck d);

int chooseScene(Session game, int turn);

Session chooseDestiny(Session session);

int findDestiny(Session session, int player);

int fullfilDestiny(Session session, int player, int destiny1, int destiny2);

Session unrevealedSecrets(Session session);

Session specialSecrets(Session session, Scene secret, int player);

Session SEEffect(Session session, Scene SE, int player);

Session reaction(Session session, Scene scene, int player, int position);

Session r19(Session session);

Session r28(Session session, int player);

Session r29(Session session, int player);

Session r30(Session session, int player);

Session r18(Session session, int player);

Session rs30(Session session, int player);

Session r16(Session session, int player);

Session reactionEffect(Session session, Scene scene, int index, int player, int choice);

Session guessAspect(Session session, int guess, int player);

Session traitGoals(Session session);

void seeBoard(Session session, int turn);
