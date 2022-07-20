#pragma once
#include "Enums.h"
#include "Scene.h"
#include "Session.h"
#include "BeforeScenes.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

Session drawScene(Session session, int chooser, std::string who, std::string deck);

Session RD(Session session, int chooser);

void RI(Session session, int player, std::string destiny);