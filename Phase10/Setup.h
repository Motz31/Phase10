#pragma once
#include "Display.h"
#include "Player.h"
#include "Card.h"
#include "Phase.h"

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>

std::vector<Player> createPlayers();
std::vector<Card> generateCards(bool);
std::vector<Phase> createPhases(int);
bool loadGame(int&, std::vector<Player>&, std::stack<Card>&, int&, std::vector<Phase>&);