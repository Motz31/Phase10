#pragma once
#include <iostream>
#include <vector>
#include "Card.h"

class Player{
	public:
		Player() {};
		Player(std::string);
		Player(std::string, int, int, bool, bool, bool, std::vector<Card>);
		~Player();
		bool stop();
		void Cstop();
		std::string getName();
		void addScore();
		int getScore();
		Card getCard(int);
		int getPhase();
		void setCard(int, Card);
		bool getPhaseComplete();
		void setPhaseComplete(bool);
		void addDownCardPart(std::vector<Card>);
		void changeDownCardPart(std::vector<Card>,int);
		void addDownCard(Card,int);
		std::vector<std::vector<Card>> getDownCards();
		bool isStopped();
		int getCardCount();
		void resetPlayer();
		void nextPhase();

		bool downThisRound = false;
	private:
		Card Cards[11];
		std::vector<std::vector<Card>> DownCards;
		bool stopped = false;
		bool PhaseComplete = false;
		int Phase = 1;
		int Score = 0;
		std::string Name = "Unknown";
		int SV[14] = { 5,5,5,5,5,5,5,5,5,10,10,10,20,20 };
};