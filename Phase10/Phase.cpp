#include "Phase.h"

Phase::Phase(){
}

Phase::Phase(int p, std::vector<int> pt, std::vector<int> pl, std::string name){
	parts = p;
	partType = pt;
	partLength = pl;
	Name = name;
}

Phase::~Phase(){
}

int Phase::getParts(){
	return parts;
}

int Phase::getPartLength(int x){
	return partLength[x];
}

int Phase::getPartType(int x){
	return partType[x];
}

std::string Phase::getName(){
	return Name;
}
