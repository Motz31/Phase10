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
	std::cout << "                           | 3 |   Anleitung   | 3 |" << std::endl;
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
		std::cout << std::setw(NameLength) << std::setw(NameLength) << p[i].getName() << " hat " << p[i].getScore() << " Punkte" << std::endl;
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

void showConfig(int PS, bool Stopper, int Autosave, bool NRs){
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
		if (NRs) {
			if ((Length - Text[i].length()) % 2)
				text << "| " << i + 1 << " |" << std::setw((Length - Text[i].length()) / 2) << " " << Text[i] << std::setw((Length - Text[i].length()) / 2 + 1) << " " << "| " << i + 1 << " |";
			else
				text << "| " << i + 1 << " |" << std::setw((Length - Text[i].length()) / 2) << " " << Text[i] << std::setw((Length - Text[i].length()) / 2) << " " << "| " << i + 1 << " |";
		}
		else {
			if ((Length - Text[i].length()) % 2)
				text << std::setw((Length - Text[i].length()) / 2) << " " << Text[i] << std::setw((Length - Text[i].length()) / 2 + 1) << " ";
			else
				text << std::setw((Length - Text[i].length()) / 2) << " " << Text[i] << std::setw((Length - Text[i].length()) / 2) << " ";
		}
		Text[i] = text.str();
		text.str("");
	}

	clear();
	showLogo();
	std::cout << "--------------------------------------------------------------------------------";
	std::cout << std::setw(33) << " " << "Konfiguration" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	if(NRs)
		for (int i = 0; i < 4; i++)
			std::cout << std::setw((80 - Length - 10) / 2) << " " << Text[i] << std::endl;
	else
		for (int i = 0; i < 3; i++)
			std::cout << std::setw((80 - Length) / 2) << " " << Text[i] << std::endl;

	if (!NRs) {
		std::cout << std::endl << "--------------------------------------------------------------------------------" << std::endl;
		std::cout << std::setw(29) << " " << "| 1 |   weiter   | 1 |" << std::endl;
		std::cout << std::setw(29) << " " << "| 2 |   " << (char)132 << "ndern   | 2 |" << std::endl;
		std::cout << std::setw(29) << " " << "| 3 |  abbrechen | 3 |" << std::endl << std::endl;
	}
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
			if (PPlaces.size() <= x)
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

void showInstructions() {
	int _IN = 0;
	int _IN2 = 0;
	do {
		_IN = 0;
		_IN2 = 0;
		clear();
		showLogo();

		std::cout << "--------------------------------------------------------------------------------";
		std::cout << "                                   Anleitung" << std::endl;
		std::cout << "--------------------------------------------------------------------------------" << std::endl;
		std::cout << std::setw(25) << " " << "| 1 | Ziel des Spieles | 1 |" << std::endl;
		std::cout << std::setw(25) << " " << "| 2 |   Spielverlauf   | 2 |" << std::endl;
		std::cout << std::setw(25) << " " << "| 3 |    die Karten    | 3 |" << std::endl;
		std::cout << std::setw(25) << " " << "| 4 |    die Phasen    | 4 |" << std::endl;
		std::cout << std::setw(25) << " " << "| 5 | Spieler Aktionen | 5 |" << std::endl;
		std::cout << std::setw(25) << " " << "| 6 |      zur" << (char)129 << "ck      | 6 |" << std::endl << std::endl;
		std::cout << "                                   Auswahl: ";

		std::cin >> _IN;
		if (_IN < 1 || _IN > 6)
			continue;
		else if (_IN == 6)
			return;
		else {
			clear();
			switch (_IN) {
				case 1: {
					std::cout << "--------------------------------------------------------------------------------";
					std::cout << std::setw(32) << " " << "Ziel des Spiels" << std::endl;
					std::cout << "--------------------------------------------------------------------------------" << std::endl;

					std::cout << "Ziel des Spieles ist es durch gezieltes Sammeln von Karten als erster alle" << std::endl;
					std::cout << "10 Phasen abzulegen. ";
					std::cout << "Sollten am Ende des Spieles zwei oder mehr Spieler auch" << std::endl;
					std::cout << "die letzte Phase abgelegt haben, dann gewinnt der Spieler mit der geringsten" << std::endl;
					std::cout << "gesamt Punkteanzahl. ";
					break;
				}
				case 2: {
					std::cout << "--------------------------------------------------------------------------------";
					std::cout << std::setw(34) << " " << "Spielverlauf" << std::endl;
					std::cout << "--------------------------------------------------------------------------------" << std::endl;

					std::cout << "Zu beginn jeder Runde bekommt jeder Spieler 10 Karten, welche nur f" << (char)129 << "r den" << std::endl;
					std::cout << "Spieler selbst sichtbar sind. Ziel einer Runde ist es mit den 10 Karten" << std::endl;
					std::cout << "die dem Spieler zur verf" << (char)129 << "gung stehen seine aktuelle Phase damit zu bilden und" << std::endl;
					std::cout << "abzulegen. Die restlichen Karten werden als verdeckter Stapel bereitgelegt." << std::endl;
					std::cout << "Die oberste Karte des verdeckten Staples wird aufgedeckt und fungiert als" << std::endl;
					std::cout << "offener Stapel. Der Spieler der an der Reihe ist muss zu beginn seines Zuges" << std::endl;
					std::cout << "eine Karte vom offenen oder vom verdeckten Stapel ziehen. Dazu tippt er eine" << std::endl;
					std::cout << "der M" << (char)148 << "glichkeiten (in diesem Fall 1 oder 2) ein und best" << (char)132 << "tigt die Auswahl mit" << std::endl;
					std::cout << "der Taste [ENTER]. Dannach kann der Spieler seine Karten mit den 8 Aktionen" << std::endl;
					std::cout << "(siehe Spieler Aktionen) verwalten. Mit der Aktion \"Karte auf Ablagestapel" << std::endl;
					std::cout << "legen\" beendet der Spieler seinen Zug und der n" << (char)132 << "chste Spieler ist an der Reihe." << std::endl;
					std::cout << "Hat ein Spieler keine Karten mehr, wird die Runde beendet, die Punkte werden" << std::endl;
					std::cout << "zusammengez" << (char)132 << "hlt und alle Abgelegten und alle Handkarten werden entfernt." << std::endl;
					break;
				}
				case 3: {
					std::cout << "--------------------------------------------------------------------------------";
					std::cout << std::setw(35) << " " << "die Karten" << std::endl;
					std::cout << "--------------------------------------------------------------------------------" << std::endl;

					std::cout << "Jede Karte besitzt einen Zahlenwert und eine Farbe. Der Zahlenwert kann" << std::endl;
					std::cout << "zwischen 1 und 12 liegen. Der Farbwert wird im Spiel wie folgt abgek" << (char)129 << "rzt: " << std::endl;
					std::cout << "\tRot = R" << std::endl;
					std::cout << "\tGr" << (char)129 << "n = G" << std::endl;
					std::cout << "\tViolett = P" << std::endl;
					std::cout << "\tGelb = Y" << std::endl << std::endl;
					std::cout << "Au" << (char)225 << "erdem gibt es zwei Sonderkarten, den Aussetzer und den Jolly." << std::endl;
					std::cout << "Mit dem Aussetzer kann man einen Spieler nach Wahl f" << (char)129 << "r eine Runde Aussetzen" << std::endl;
					std::cout << "lassen. Ein Aussetzer wird im Spiel als Ausrufezeichen dargestellt (!!!)" << std::endl << std::endl;
					std::cout << "Der Jolly kann jede Farbe und jeden Zahlenwert annehmen und kann fehlende" << std::endl;
					std::cout << "Karten ersetzten, Im Spiel wird der Jolly als Stern dargestellt (***)." << std::endl;
					std::cout << "Der Jolly kann jedoch nicht mehr ersetzt werden sobald die Phase abgelegt" << std::endl;
					std::cout << "worden ist.";
					break;
				}
				case 4: {
					std::cout << "--------------------------------------------------------------------------------";
					std::cout << std::setw(35) << " " << "die Phasen" << std::endl;
					std::cout << "--------------------------------------------------------------------------------" << std::endl;

					std::cout << "Jede Phase kann aus ein oder mehreren teilen bestehen. Dabei gibt es vier" << std::endl;
					std::cout << "verschiedene Arten von Teilen:" << std::endl;
					std::cout << "\t1. Gleiche Zahl" << std::endl;
					std::cout << "\t2. Gleiche Farbe" << std::endl;
					std::cout << "\t3. Zahlenfolge" << std::endl;
					std::cout << "\t4. Zahlenfolge gleicher Farbe" << std::endl << std::endl;
					std::cout << "Bei Phasen gleicher Zahlen oder gleicher Farben darf mindestens eine Karte kein" << std::endl;
					std::cout << "Jolly sein, bei Zahlenfolgen m" << (char)129 << "ssen es mindestens zwei sein." << std::endl << std::endl;
					std::cout << "Alle Karten eines Teils m" << (char)129 << "ssen der vorgegebenen Art des Teils entsprechen." << std::endl;
					std::cout << "Ist eine Phase komplett kann sie offen f" << (char)129 << "r alle Spieler abgelegt werden." << std::endl;
					std::cout << "Durch das ablegen der Phase ist der Spieler berechtigt in der n" << (char)132 << "chsten Runden" << std::endl;
					std::cout << "mit der n" << (char)132 << "chsten Phase fortzusetzen. ";
					break;
				}
				case 5: {
				_IN2 = 0;
				do {
					clear();
					showLogo();
					std::cout << "--------------------------------------------------------------------------------";
					std::cout << std::setw(32) << " " << "Spieler Aktionen" << std::endl;
					std::cout << "--------------------------------------------------------------------------------" << std::endl;
					std::cout << std::setw(20) << " " << "| 1 |       Karten sortieren       | 1 |" << std::endl;
					std::cout << std::setw(20) << " " << "| 2 | Karte auf Ablagestapel legen | 2 |" << std::endl;
					std::cout << std::setw(20) << " " << "| 3 | Phasen der Spieler anzeigen  | 3 |" << std::endl;
					std::cout << std::setw(20) << " " << "| 4 | Punkte der Spieler anzeigen  | 4 |" << std::endl;
					std::cout << std::setw(20) << " " << "| 5 |  Abgelegte Karten anzeigen   | 5 |" << std::endl;
					std::cout << std::setw(20) << " " << "| 6 |  Karten ablegen / erweitern  | 6 |" << std::endl;
					std::cout << std::setw(20) << " " << "| 7 |       Spiel Speichern        | 7 |" << std::endl;
					std::cout << std::setw(20) << " " << "| 8 |     zur" << (char)129 << "ck zum Hauptmen" << (char)129 << "     | 8 |" << std::endl;
					std::cout << std::setw(20) << " " << "| 9 |            zur" << (char)129 << "ck            | 9 |" << std::endl << std::endl;
					std::cout << "                                   Auswahl: ";

					std::cin >> _IN2;

					if (_IN2 < 0 || _IN2 > 9)
						continue;
					else if (_IN2 == 9)
						break;
					else {
						clear();
						switch (_IN2) {
							case 1: {
								std::cout << "--------------------------------------------------------------------------------";
								std::cout << std::setw(32) << " " << "Karten sortieren" << std::endl;
								std::cout << "--------------------------------------------------------------------------------" << std::endl;
								std::cout << "Mit dieser Aktion kann der Spieler seine Karten sortieren." << std::endl;
								std::cout << "Dazu tippt der Spieler die jeweiligen Nummern der Karten ein, welche den Platz" << std::endl;
								std::cout << "miteinander tauschen sollen. Die Eingabe wird mit [ENTER] best" << (char)132 << "tigt.";
								break;
							}
							case 2: {
								std::cout << "--------------------------------------------------------------------------------";
								std::cout << std::setw(26) << " " << "Karte auf Ablagestapel legen" << std::endl;
								std::cout << "--------------------------------------------------------------------------------" << std::endl;
								std::cout << "Mit dieser Aktion legt der Spieler eine Karte seiner Wahl auf den Ablagestapel. ";
								std::cout << "Die Nummer der Karte wird eingegeben und mit [ENTER] best" << (char)132 << "tigt. Befindet sich" << std::endl;
								std::cout << "auf dem ausgew" << (char)132 << "hltem Platz ein Aussetzter, wird der Spieler gefragt welcher" << std::endl;
								std::cout << "andere Spieler diesen Aussetzter erhalten soll. Hat der ausgew" << (char)132 << "hlte Spieler" << std::endl;
								std::cout << "bereits einen Aussetzter von einem anderen Spieler erhalten, so kann dieser" << std::endl;
								std::cout << "nicht noch einen erhalten und ein anderer Spieler muss gew" << (char)132 << "hlt werden." << std::endl << std::endl;
								std::cout << "Besitzt der Spieler nur noch eine Karte, dann kann er mit der" << std::endl;
								std::cout << "Aktion \"2 | Runde beenden\" die Runde beenden. Besitz der Spieler jedoch noch" << std::endl;
								std::cout << "mehrere Karten wir sein Zug beendet und der n" << (char)132 << "chste Spieler kommt an die Reihe.";
								break;
							}
							case 3: {
								std::cout << "--------------------------------------------------------------------------------";
								std::cout << std::setw(26) << " " << "Phasen der Spieler anzeigen" << std::endl;
								std::cout << "--------------------------------------------------------------------------------" << std::endl;
								std::cout << "Mit dieser Aktion kann sich der Spieler die Phasen aller Spielern anzeigen" << std::endl;
								std::cout << "lassen.";
								break;
							}
							case 4: {
								std::cout << "--------------------------------------------------------------------------------";
								std::cout << std::setw(26) << " " << "Karten der Spieler anzeigen" << std::endl;
								std::cout << "--------------------------------------------------------------------------------" << std::endl;
								std::cout << "Mit dieser Aktion kann sich der Spieler die Punktest" << (char)132 << "nde aller Spieler anzeigen" << std::endl;
								std::cout << "lassen.";
								break;
							}
							case 5: {
								std::cout << "--------------------------------------------------------------------------------";
								std::cout << std::setw(27) << " " << "Abgelegte Karten anzeigen" << std::endl;
								std::cout << "--------------------------------------------------------------------------------" << std::endl;
								std::cout << "Mit dieser Aktion kann sich der Spieler die Abgelegten Karten der Spieler" << std::endl;
								std::cout << "anzeigen lassen.";
								break;
							}
							case 6: {
								std::cout << "--------------------------------------------------------------------------------";
								std::cout << std::setw(26) << " " << "Karten ablegen / erweitern" << std::endl;
								std::cout << "--------------------------------------------------------------------------------" << std::endl;
								std::cout << "Mit dieser Aktion kann der Spieler seine Karten ablegen." << std::endl;
								std::cout << "Hat dieser seine Karten bereits abgelegt kann er seine eigenen oder andere mit" << std::endl;
								std::cout << "dieser Aktion erweitern. Der Spieler muss die Phase wie auf dem Bildschirm" << std::endl;
								std::cout << "beschrieben ablegen. Dazu gibt der Spieler die jeweilige Kartennummer an und" << std::endl;
								std::cout << "best" << (char)132 << "tigt mit [ENTER]." << std::endl;
								std::cout << "Bei erfolgreicher Eingabe werden die Karten abgelegt und aus den Kandkarten" << std::endl;
								std::cout << "entfernt. Wurde die Phase nicht korrekt abgelegt, wird eine Fehlermeldung mit" << std::endl;
								std::cout << "dem Grund des Scheiterns ausgegeben." << std::endl << std::endl;
								std::cout << "Hat der Spieler seine Phase bereits abgelegt, wird stattdessen die" << std::endl;
								std::cout << "Aktion \"6 | abgelegt Karten erweitern\" angezeigt." << std::endl;
								std::cout << "Mit dieser Aktion kann der Spieler seine Handkarten bei bereits abgelegten" << std::endl;
								std::cout << "Karten anlegen, wenn diese die Phase passend Fortsetzten. z.b. wenn die" << std::endl;
								std::cout << "Phase \"7 Karten einer Farbe\" abgelegt wurde, muss die Phase mit derselben" << std::endl;
								std::cout << "Farbe erweitert werden in der sie abgelegt wurde. Dies gilt genauso f" << (char)129 << "r die" << std::endl;
								std::cout << "anderen Arten von Teilen, siehe Seite \"die Phasen\"";
								break;
							}
							case 7: {
								std::cout << "--------------------------------------------------------------------------------";
								std::cout << std::setw(32) << " " << "Spiel Speichern" << std::endl;
								std::cout << "--------------------------------------------------------------------------------" << std::endl;
								std::cout << "Mit dieser Aktion wird das Spiel zum aktuellen Zeitpunkt gespeichert damit zu" << std::endl;
								std::cout << "einem sp" << (char)132 << "teren Zeitpunkt auch nach beenden des Programmes weitergespielt werden" << std::endl;
								std::cout << "kann.";

								break;
							}
							case 8: {
								std::cout << "--------------------------------------------------------------------------------";
								std::cout << std::setw(30) << " " << "zur" << (char)129 << "ck zum Hauptmen" << (char)129 << std::endl;
								std::cout << "--------------------------------------------------------------------------------" << std::endl;
								std::cout << "Mit dieser Aktion gelangt der Spieler zur" << (char)129 << "ck zum Hautpmen" << (char)129 << ". Allerdings wird" << std::endl;
								std::cout << "das Spiel dabei NICHT gespeichert.";
								break;
							}
						}
					}
					std::cout << std::endl << std::endl;
					if (_IN2 != 9)
						waitForEnter();
				} while (true);
				break;
			}
			}
		}
		std::cout << std::endl << std::endl;
		if (!_IN2)
			waitForEnter();
	} while (true);
	waitForEnter();
}

