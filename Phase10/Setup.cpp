#include "Setup.h"

std::vector<Player> createPlayers(){
	std::vector<Player> Players;
	int PlayerCount = 0;

	do {
		clear();
		showLogo();
		PlayerCount = 0;
		std::cout << "Anzahl der Spieler: ";
		std::cin >> PlayerCount;
	} while (PlayerCount < 2 || PlayerCount > 6);

	for (int i = 0; i < PlayerCount; i++) {
		std::string name = "";

		clear();
		showLogo();

		std::cout << "Name von Spieler " << i+1 << ": ";

		std::cin >> name;
		Players.push_back(Player(name));
		
		clear();
	}

	clear();

	return Players;
}

std::vector<Card> generateCards(bool Stopper){
	std::string colors[4]{ "R", "Y", "G", "P" };
	std::vector<Card> AllCards;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 12; j++) {
			AllCards.push_back(Card(j + 1, colors[i]));
			AllCards.push_back(Card(j + 1, colors[i]));
		}
	}

	for (int i = 0; i < 8; i++) {
		AllCards.push_back(Card(13, "*"));
	}
	if (Stopper) {
		for (int i = 0; i < 4; i++) {
			AllCards.push_back(Card(14, "!"));
		}
	}
	return AllCards;
}

std::vector<Phase> createPhases(int x){
	std::vector<Phase> Phases;

	std::string Names[2][10] = { {
		"2 Drillinge",
		"1 Drilling + 1 Viererfolge",
		"1 Vierling + 1 Viererfolge",
		"1 Siebenerfolge",
		"1 Achterfolge",
		"1 Neunerfolge",
		"2 Vierlinge",
		"7 Karten einer Farbe",
		"1 Fünfling + 1 Zwilling",
		"1 Fünfling + 1 Drilling"
	}, {
		"4 Zwillinge",
		"6 Karten einer Farbe",
		"1 Vierling + 1 Viererfolge",
		"1 Achterfolge",
		"7 Karten einer Farbe",
		"1 Neunerfolge",
		"2 Vierlinge",
		"1 Viererfolge einer Farbe + 1 Drilling",
		"1 Fünfling + 1 Drilling",
		"1 Fünfling + 1 Dreierfolge einer Farbe"
	} };

	std::stringstream text;
	text << "1 F" << (char)129 << "nfling + 1 Zwilling";
	Names[0][8] = text.str();
	text.str("");

	text << "1 F" << (char)129 << "nfling + 1 Drilling";
	Names[0][9] = text.str();
	text.str("");

	text << "1 F" << (char)129 << "nfling + 1 Drilling";
	Names[1][8] = text.str();
	text.str("");

	text << "1 F" << (char)129 << "nfling + 1 Dreierfolge einer Farbe";
	Names[1][9] = text.str();
	text.str("");

	int PA[2][10][9] = {{
		{ 2,1,1,3,3,0,0,0,0 },
		{ 2,1,3,3,4,0,0,0,0 },
		{ 2,1,3,4,4,0,0,0,0 },
		{ 1,3,7,0,0,0,0,0,0 },
		{ 1,3,8,0,0,0,0,0,0 },
		{ 1,3,9,0,0,0,0,0,0 },
		{ 2,1,1,4,4,0,0,0,0 },
		{ 1,2,7,0,0,0,0,0,0 },
		{ 2,1,1,5,2,0,0,0,0 },
		{ 2,1,1,5,3,0,0,0,0 }
	}, {
		{ 4,1,1,1,1,2,2,2,2 },
		{ 1,2,6,0,0,0,0,0,0 },
		{ 2,1,3,4,4,0,0,0,0 },
		{ 1,3,8,0,0,0,0,0,0 },
		{ 1,2,7,0,0,0,0,0,0 },
		{ 1,3,9,0,0,0,0,0,0 },
		{ 2,1,1,4,4,0,0,0,0 },
		{ 2,4,1,4,3,0,0,0,0 },
		{ 2,1,1,5,3,0,0,0,0 },
		{ 2,1,4,5,3,0,0,0,0 }
	}};

	for (int i = 0; i < 10; i++) {
		std::vector<int> Type;
		std::vector<int> Length;

		for (int k = 0; k < PA[x][i][0]; k++) {
			Type.push_back(PA[x][i][1 + k]);
		}

		for (int k = 0; k < PA[x][i][0]; k++) {
			Length.push_back(PA[x][i][1 + k + PA[x][i][0]]);
		}

		Phases.push_back(Phase(PA[x][i][0],Type,Length, Names[x][i]));
	}

	return Phases;
}

bool loadGame(int& LAP, std::vector<Player>& Lp, std::stack<Card>& LdCards, int& LRound, std::vector<Phase>& LPhases){
	std::fstream file("save.txt", std::ios::in);

	if (!file) {
		std::cout << "Fehler: Datei konnte nicht gefunden oder ge" << (char)148 << "ffnet werden!" << std::endl << std::endl;
		errLoadingSave();
		return false;
	}

	std::string line;
	std::getline(file, line);

	std::vector<std::string> LS;

	/*Allgemeines laden*/
	/*; entfernen und Werte in Array speichern*/
	std::string data;

	for (int i = 0; i < line.length(); i++) {
		if (line[i] == ';' && data.size()) {
			LS.push_back(data);
			data = "";
		}
		else if(line[i] != ';'){
			data += line[i];
		}
	}

	int PNr = stoi(LS[0]);
	LAP = stoi(LS[1]);
	LRound = stoi(LS[2]);
	int LPhaseSet = stoi(LS[3]);
	
	LPhases = createPhases(LPhaseSet);

	/*Spieler laden*/
	/*; entfernen und Werte in Array speichern*/
	for (int i = 0; i < PNr; i++) {
		LS.clear();
		getline(file, line);

		for (int k = 0; k < line.length(); k++) {
			if (line[k] == ';' && data.size()) {
				LS.push_back(data);
				data = "";
			}
			else if(line[k] != ';'){
				data += line[k];
			}
		}

		std::string PName = LS[0];
		int PPhase = stoi(LS[1]);
		int PScore = stoi(LS[2]);
		bool PStopped = stoi(LS[3]);
		bool PPhaseComplete = stoi(LS[4]);
		bool PDownThisRound = stoi(LS[5]);

		std::vector<Card> Cards;

		for (int j = 0; j < 11; j++) {
			Cards.push_back(Card(stoi(LS[6 + 2 * j + 1]),LS[6 + 2 * j]));
		}

		Lp.push_back(Player(PName,PPhase, PScore, PStopped, PPhaseComplete, PDownThisRound, Cards));
	}

	/*DiscardStack laden*/
	LS.clear();

	getline(file, line);

	for (int k = 0; k < line.length(); k++) {
		if (line[k] == ';' && data.size()) {
			LS.push_back(data);
			data = "";
		}
		else if (line[k] != ';') {
			data += line[k];
		}
	}

	for (int i = 0; i < LS.size(); i += 2) {
		LdCards.push(Card(stoi(LS[i+1]),LS[i]));
	}

	/*DownCards*/
	for (int i = 0; i < PNr; i++) {
		if (Lp[i].getPhaseComplete() || Lp[i].downThisRound) {
			for (int k = 0; k < LPhases[Lp[i].getPhase() - 1].getParts(); k++) {
				getline(file, line);

				LS.clear();

				for (int l = 0; l < line.length(); l++) {
					if (line[l] == ';' && data.size()) {
						LS.push_back(data);
						data = "";
					}
					else if (line[l] != ';') {
						data += line[l];
					}
				}

				// INFO : Wenn letzter Datensatz dahinter kein Semikolon hat wir er nicht abgespeicher
				std::vector<Card> Part;

				for (int l = 0; l < LS.size(); l += 2) {
					Part.push_back(Card(stoi(LS[l + 1]), LS[l]));
				}
				Lp[i].addDownCardPart(Part);
			}
		}
	}
	return true;
}
