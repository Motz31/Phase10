#pragma once
#include <string>

class Card{
	public:
		Card();
		Card(int nr, std::string c);
		~Card();
		void setValue(int);
		void setColor(std::string);
		int getValue();
		std::string getColor();
	private:
		int Value;
		std::string Color;
};