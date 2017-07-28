#pragma once
#include "Card.h"
#include "Player.h"
#include "Display.h"

#include <vector>
#include <stack>
#include <random>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>

Card pullCard(std::vector<Card>);
int random(int, int);
std::vector<Player> prepareRound(std::vector<Player>, std::vector<Card>);
Player pickCard(Player, std::vector<Player>, std::stack<Card>&, std::vector<Card>, std::vector<Phase>);
int getCommand(Player,std::vector<Phase>,bool = false);
bool checkEnd(Player);
Player swapCards(Player, std::vector<Phase>);
void expandDownCards(Player&, std::vector<Player>&, std::vector<Phase>);
void finishPhase(Player&, std::vector<Phase>);
int checkPhase(int, int, std::vector<Card>);
bool stopPlayer(Player, std::vector<Player>&, int, std::vector<Phase>);
void endRound(std::vector<Player>&, std::stack<Card>&);
bool saveGame(int, std::vector<Player>, std::stack<Card>, int, std::vector<Phase>, int);
int discardCard(Player, std::vector<Phase>);