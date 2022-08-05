#pragma once
#include "Enums.h"
#include "Scene.h"
#include "Session.h"
#include "BeforeScenes.h"
#include "Shuffle.h"
#include <vector>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

Session drawScene(Session session, int chooser, std::string who, std::string deck);

Session RD(Session session, int chooser);

void RI(Session session, int player, std::string destiny);

void RK(Session session, int player);

void RR(Session session, int player);

Session SI(Session session, int chooser, std::string destiny);

Session SO(Session session, int chooser, std::string destiny);

Session DD(Session session, int player, std::string destiny);

Session RE(Session session, int chooser, std::string destiny);

Session CO(Session session, int chooser);

Session SWO(Session session);

Session CTT(Session session, int chooser);

Session CRT(Session session, int chooser);

Session DS(Session session, int chooser, std::string number);

Session TRADE(Session session);

void STELLL(Session session, int chooser);

Session DRC(Session session, int player);