#include "Card.h"

Card::Card(){
}

Card::Card(int x, std::string c){
	Value = x;
	Color = c;
}

Card::~Card(){
}

void Card::setValue(int x){
	Value = x;
}

void Card::setColor(std::string c){
	Color = c;
}

int Card::getValue(){
	return Value;
}

std::string Card::getColor(){
	return Color;
}
