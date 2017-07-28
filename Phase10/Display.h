#pragma once
#include "Player.h"
#include "Phase.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>

void showLogo();
void showGameOver();
void showMM();
void clear();
void RoundStart(int);
void nextPlayer(std::string);
void waitForEnter();
void playerCards(Player, std::vector<Phase>, bool = false);
std::string PhaseTypeName(int);
void PlayerPhases(std::vector<Player>, std::vector<Phase>);
void PlayerScores(std::vector<Player>);
void showDownCards(std::vector<Player>, std::vector<Phase>, bool = false, bool = false, bool = true);
void stoppedText();
void RoundEndScreen(Player, std::vector<Player>, int, std::vector<Phase>);
void showConfig(int,bool,int,bool = true);
void endGame(std::vector<Player>);
void errLoadingSave();
void showInstructions();