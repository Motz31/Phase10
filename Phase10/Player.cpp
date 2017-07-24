#include "Player.h"

Player::Player(std::string n){
	Name = n;
}

Player::Player(std::string n, int p, int sc, bool st, bool pc, bool dtr, std::vector<Card> c){
	Name = n;
	Phase = p;
	Score = sc;
	stopped = st;
	PhaseComplete = pc;
	downThisRound = dtr;
	for (int i = 0; i < 11; i++) {
		Cards[i] = c[i];
	}
}

Player::~Player(){
}

bool Player::stop(){
	if (stopped)
		return true;
	else {
		stopped = true;
		return false;
	}
}

void Player::Cstop(){
	stopped = false;
}

std::string Player::getName(){
	return Name;
}

void Player::addScore(){
	for(int i = 0; i < 10; i++){
		if (Cards[i].getValue() == 0)
			continue;
		Score += SV[Cards[i].getValue() - 1];
	}
}

int Player::getScore(){
	return Score;
}

Card Player::getCard(int x){
	return Cards[x];
}

int Player::getPhase(){
	return Phase;
}

void Player::setCard(int x, Card c){
	Cards[x] = c;
}

bool Player::getPhaseComplete(){
	return PhaseComplete;
}

void Player::setPhaseComplete(bool x){
	PhaseComplete = x;
}

void Player::addDownCardPart(std::vector<Card> v){
	DownCards.push_back(v);
}

void Player::changeDownCardPart(std::vector<Card> Cards, int x){
	if (x > DownCards.size() - 1)
		std::cout << "ERROR: Part nicht vorhanden!";
	else
		DownCards[x] = Cards;
}

void Player::addDownCard(Card C, int x){
	DownCards[x].push_back(C);
}

void Player::resetPlayer(){
	DownCards.clear();
	Cstop();
	downThisRound = false;
	PhaseComplete = false;
	for (int i = 0; i < 11; i++) {
		Cards[i] = Card(0, "-");
	}
}

void Player::nextPhase(){
	Phase++;
}

std::vector<std::vector<Card>> Player::getDownCards(){
	return DownCards;
}

bool Player::isStopped(){
	return stopped;
}

int Player::getCardCount(){
	int count = 0;
	for (int i = 0; i < 11; i++) {
		if (Cards[i].getValue())
			count++;
	}
	return count;
}
