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

Session situationEffect(Session session, Scene situation, int player);