#pragma once
#include <vector>

class Phase{
	public:
		Phase();
		Phase(int, std::vector<int>, std::vector<int>, std::string);
		~Phase();
		int getParts();
		int getPartLength(int);
		int getPartType(int);
		std::string getName();
	private:
		int parts;
		std::vector<int> partLength;
		std::vector<int> partType;
		std::string Name;
};

