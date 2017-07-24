#pragma once
#include "Display.h"

void showLogo() {
	std::cout << "             ______                                           _____ " << std::endl;
	std::cout << "            |      |  |                                  /|  |     |" << std::endl;
	std::cout << "            |      |  |                ___    ___       / |  |     |" << std::endl;
	std::cout << "            |______|  |____    ____|  |      |   |     /  |  |     |" << std::endl;
	std::cout << "            |         |    |  |    |  |___   |___|        |  |     |" << std::endl;
	std::cout << "            |         |    |  |    |      |  |            |  |     |" << std::endl;
	std::cout << "            |         |    |  |____|   ___|  |___         |  |_____|" << std::endl;
	std::cout << std::endl;
}

void showGameOver() {
	std::cout << "   _______  _______  _______  _______    _______           _______  _______ " << std::endl;
	std::cout << "  (  ____ \(  ___  )(       )(  ____ \  (  ___  )|\     /|(  ____ \(  ____ )" << std::endl;
	std::cout << "  | (    \/| (   ) || () () || (    \/  | (   ) || )   ( || (    \/| (    )|" << std::endl;
	std::cout << "  | |      | (___) || || || || (__      | |   | || |   | || (__    | (____)|" << std::endl;
	std::cout << "  | | ____ |  ___  || |(_)| ||  __)     | |   | |( (   ) )|  __)   |     __)" << std::endl;
	std::cout << "  | | \_  )| (   ) || |   | || (        | |   | | \ \_/ / | (      | (\ (   " << std::endl;
	std::cout << "  | (___) || )   ( || )   ( || (____/\  | (___) |  \   /  | (____/\| ) \ \__" << std::endl;
	std::cout << "  (_______)|/     \||/     \|(_______/  (_______)   \_/   (_______/|/   \__/" << std::endl;
	std::cout << std::endl;
}

void showMM() {
	clear();
	showLogo();
	std::cout << "--------------------------------------------------------------------------------";
	std::cout << "                                   Hauptmen" << (char)129 << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "                           | 1 |  Neues Spiel  | 1 |" << std::endl;
	std::cout << "                           | 2 |  Spiel laden  | 2 |" << std::endl;
	std::cout << "                           | 3 | Einstellungen | 3 |" << std::endl;
	std::cout << "                           | 4 | Spiel beenden | 4 |" << std::endl << std::endl;
	std::cout << "                                   Auswahl: ";
}

void clear() {
	system("cls");
}

void RoundStart(int n){
	clear();
	showLogo();
	std::cout << "--------------------------------------------------------------------------------";
	std::cout << "                              Runde " << n << " hat begonnen!" << std::endl;
	std::cout << "--------------------------------------------------------------------------------";

	waitForEnter();
}

void nextPlayer(std::string n) {
	clear();
	showLogo();

	int length = n.length() + 18;
	std::cout << "--------------------------------------------------------------------------------";
	for (int i = 0; i < (80 - length) / 2; i++) {
		std::cout << " ";
	}
	std::cout << n << " ist an der Reihe!" << std::endl;
	std::cout << "--------------------------------------------------------------------------------";

	waitForEnter();
}

void waitForEnter(){
	/*while (GetAsyncKeyState(0x0D) < 0) {}
	Sleep(1000);
	while (GetAsyncKeyState(0x0D) < 0) {}*/
	system("PAUSE");
}

void playerCards(Player p, std::vector<Phase> Phases, bool showNumbers){
	std::cout << "Ihre Phase: " << Phases[p.getPhase() - 1].getName() << std::endl << std::endl;
	std::cout << "Ihre Karten: ";
	for (int j = 0; j < 11; j++) {
		std::string Color = p.getCard(j).getColor();
		std::string Number = std::to_string(p.getCard(j).getValue());
		/*Jolly und Aussetzer korrektur*/
		if (Number == "13") {
			Number = "**";
		}
		if (Number == "14") {
			Number = "!!";
		}
		if (Number == "0") {
			Number = "--";
		}
		std::cout << std::setfill('0');
		std::cout << std::setw(1) << Color << std::setw(2) << Number << " | ";
		std::cout << std::setfill(' ');
	}
	if (showNumbers) {
		std::cout << std::endl << std::setw(14) << "";

		for (int i = 1; i <= 11; i++) {
			std::cout << std::left << std::setw(2) << i << " |  " << std::right;
		}
	}

	std::cout << std::endl;
}

std::string PhaseTypeName(int x){
	std::string Desc[4] = {
		"mit dem selben Zahlenwert an!",
		"mit der selben Farbe an!",
		"in auf oder absteigender Reihenfolge an!",
		"in auf oder absteigender Reihenfolge und in der selben Farbe an!"
	};

	return Desc[x];
}

void PlayerPhases(std::vector<Player> p, std::vector<Phase> Phases){
	unsigned int NameLength = 0;
	for (unsigned int i = 0; i < p.size(); i++) {
		if(p[i].getName().length() > NameLength)
			NameLength = p[i].getName().length();
	}

	std::cout << std::endl;
	for (unsigned int i = 0; i < p.size(); i++) {
		std::cout << std::setw(NameLength) << p[i].getName() << " ist bei Phase " << p[i].getPhase() << ": " << Phases[p[i].getPhase() - 1].getName() << std::endl;
	}
	std::cout << std::endl;
	waitForEnter();
}

void PlayerScores(std::vector<Player> p) {
	unsigned int NameLength = 0;
	for (unsigned int i = 0; i < p.size(); i++) {
		if (p[i].getName().length() > NameLength)
			NameLength = p[i].getName().length();
	}

	std::cout << std::endl;
	for (unsigned int i = 0; i < p.size(); i++) {
		std::cout << std::setw(NameLength) << "Der Score von " << std::setw(NameLength) << p[i].getName() << " ist: " << p[i].getScore() << std::endl;
	}
	std::cout << std::endl;
	waitForEnter();
}

void showDownCards(std::vector<Player> p, std::vector<Phase> Phases, bool x, bool Nr, bool Enter){
	unsigned int NameLength = 0;
	for (unsigned int i = 0; i < p.size(); i++) {
		if (p[i].getName().length() > NameLength)
			NameLength = p[i].getName().length();
	}

	std::cout << std::endl;

	for (int i = 0; i < p.size(); i++) {
		if (p[i].getPhaseComplete() || p[i].downThisRound) {
			std::vector<std::vector<Card>> Cards = p[i].getDownCards();

			if (Nr)
				std::cout << i+1 << " | ";

			std::cout << std::setw(NameLength) << p[i].getName() << " | Phase: " << Phases[p[i].getPhase() - 1].getName() << std::endl << std::endl;
			std::cout << std::setw(NameLength) << " " << "   Karten: ";

			for (int k = 0; k < Phases[p[i].getPhase() - 1].getParts(); k++) {
				std::cout << "Teil " << k + 1 << ": ";

				int Length = Cards[k].size();

				/*Die Karten werden dargestellt*/
				for (int l = 0; l < Length; l++) {
					std::string Color = Cards[k][l].getColor();
					std::string Number = std::to_string(Cards[k][l].getValue());

					/*Jolly und Aussetzer korrektur*/
					if (Number == "13") {
						Number = "**";
					}
					if (Number == "14") {
						Number = "!!";
					}
					std::cout << std::setfill('0');
					std::cout << std::setw(1) << Color << std::setw(2) << Number << " | ";
					std::cout << std::setfill(' ');
				}
				std::cout << std::endl;
				std::cout << std::setw(NameLength + 11) << "";
			}
			std::cout << std::endl;
		}
		else if(!x){
			std::cout << std::setw(NameLength) << p[i].getName() << " | Spieler hat seine Phase noch nicht abgelegt!" << std::endl << std::endl;
		}
	}
	if(Enter)
		waitForEnter();
}

void stoppedText(){
	clear();
	showLogo();
	std::cout << "--------------------------------------------------------------------------------";
	std::cout << "    Du hast einen Aussetzer erhalten und muss deshalb diese Runde aussetzen!" << std::endl;
	std::cout << "--------------------------------------------------------------------------------";

	waitForEnter();
}

void RoundEndScreen(Player player, std::vector<Player> p, int Round, std::vector<Phase> Phases) {
	clear();

	for (int i = 0; i < (80 - player.getName().length() - 23) / 2; i++)
		std::cout << " ";
	std::cout << player.getName() << " hat die " << Round << ".Runde gewonnen" << std::endl;

	for (int i = 0; i < p.size(); i++) {
		std::cout << p[i].getName() << ":" << std::endl;

		std::cout << "\tPhase abgelegt: ";
		if (p[i].getPhaseComplete())
			std::cout << "Ja" << std::endl;
		else
			std::cout << "Nein" << std::endl;

		std::cout << "\tN" << (char)132 << "chste Phase: " << Phases[p[i].getPhase() - 1].getName() << std::endl;

		std::cout << "\tScore: " << std::setfill('0') << std::setw(4) << p[i].getScore() << std::endl << std::endl;
	}

	waitForEnter();
}

void showSettings(int PS, bool Stopper, int Autosave){
	int Length = 0;
	std::string Text[4];
	std::string PhaseSets[2] = { "Klassik", "Master" };
	std::string AS[3] = { "Aus", "zu Rundenbeginn", "bei Spielerwechsel" };
	std::string YN[2] = {"Nein",  "Ja" };
	std::stringstream text;

	Text[0] = "Phasen: " + PhaseSets[PS];
	Text[1] = "Aussetzer: " + YN[Stopper];
	Text[2] = "Autosave: " + AS[Autosave];
	text << "zur" << (char)129 << "ck";
	Text[3] = text.str();

	text.str("");

	for (int i = 0; i < 4; i++) {
		if (Length < Text[i].length())
			Length = Text[i].length();
	}

	Length += 2;

	for (int i = 0; i < 4; i++) {
		if((Length - Text[i].length()) % 2)
			text << "| " << i + 1 << " |" << std::setw((Length - Text[i].length()) / 2) << " " << Text[i] << std::setw((Length - Text[i].length()) / 2 + 1) << " " << "| " << i + 1 << " |";
		else
			text << "| " << i+1 << " |" << std::setw((Length - Text[i].length())/2) << " " << Text[i] << std::setw((Length - Text[i].length()) / 2) << " " << "| " << i+1 << " |";
		Text[i] = text.str();
		text.str("");
	}

	clear();
	showLogo();
	std::cout << "--------------------------------------------------------------------------------";
	std::cout << "                                 Einstellungen" << std::endl;
	std::cout << "--------------------------------------------------------------------------------";
	std::cout << std::endl;

	for (int i = 0; i < 4; i++) {
		std::cout << std::setw((80 - Length - 10) / 2) << " " << Text[i] << std::endl;
	}

	std::cout << std::endl << "                                   Auswahl: ";
}

void endGame(std::vector<Player> p) {
	std::vector<Player> PPlaces;
	int maxPhase = 1;
	int minScore = 0;
	int secPlayer = 0;

	while (!p.empty()) {
		maxPhase = 1;
		minScore = 0;
		secPlayer = 0;
		for (int i = 0; i < p.size(); i++) {
			if (p[i].getPhase() > maxPhase) {
				maxPhase = p[i].getPhase();
				minScore = p[i].getScore();
				secPlayer = i;
			}
			else if (p[i].getPhase() == maxPhase && p[i].getScore() < minScore) {
				minScore = p[i].getScore();
				secPlayer = i;
			}
		}
		PPlaces.push_back(p[secPlayer]);
		p.erase(p.begin()+secPlayer);
	}
	
	clear();
	showLogo();
	//showGameOver();
	std::cout << "--------------------------------------------------------------------------------";
	std::cout << std::setw(33) << " " << "Platzierungen" << std::endl;
	std::cout << "--------------------------------------------------------------------------------";

	std::string line;
	for (int i = 0; i < 8; i++) {
		line += (char)196;
	}

	int x = 0;
	int i = 1;
	while (x < PPlaces.size()) {
		std::cout << std::setw(35) << " " << (char)218 << line << (char)191 << std::endl;
		std::cout << std::setw(35) << " " << (char)179 << i << ". Platz" << (char)179 << std::endl;
		std::cout << std::setw(35) << " " << (char)192 << line << (char)217 << std::endl;

		do {
			int _width = 80 - PPlaces[x].getName().size();

			std::cout << std::setw(_width/2) << " " << PPlaces[x].getName() << std::endl;
			x++;
			if (PPlaces.size() <= x + 1)
				break;
		} while (PPlaces[x - 1].getScore() == PPlaces[x].getScore() && PPlaces[x - 1].getPhase() == PPlaces[x].getPhase());

		i++;
		std::cout << std::endl;
	}
}

void errLoadingSave(){
	clear();
	showLogo();
	std::cout << "--------------------------------------------------------------------------------";
	std::cout << std::setw(19) << " " << "Es konnte kein Spielstand gefunden werden!" << std::endl;
	std::cout << "--------------------------------------------------------------------------------";

	waitForEnter();
}
