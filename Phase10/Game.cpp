#include "Game.h"

Card pullCard(std::vector<Card> Cards) {
	return Cards[random(0, Cards.size() - 1)];
}

int random(int _min, int _max) {
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(_min, _max);
	return distribution(generator);
}

std::vector<Player> prepareRound(std::vector<Player> Players, std::vector<Card> AllCards) {
	/*Karten austeilen*/
	for (unsigned int j = 0; j < Players.size(); j++){
		for (int k = 0; k < 10; k++) {
			Players[j].setCard(k, pullCard(AllCards));
		}
		Players[j].setCard(10, Card(0,"-"));
	}

	return Players;
}

Player pickCard(Player p, std::vector<Player> Players, std::stack<Card> &dCards, std::vector<Card> AllCards, std::vector<Phase> Phases){
	playerCards(p,Phases);
	int cStack = 0;

	do {
		clear();
		cStack = 0;

		playerCards(p, Phases);

		std::string Color;
		std::string Number;

		if (dCards.empty()) {
			Color = "-";
			Number = "--";
		}
		else {
			Color = dCards.top().getColor();
			Number = std::to_string(dCards.top().getValue());
		}
		
		std::cout << std::endl << "Ziehe eine Karte vom offenen oder vom verdeckten Stapel!" << std::endl << std::endl;

		if (Number == "13")
			Number = "**";

		if (Number == "14")
			Number = "!!";

		std::cout << "   1   |   2   |            3" << std::endl;
		std::cout << "  " << std::setfill('0') << std::setw(1) << Color << std::setw(2) << Number << "  | " << " ??? " << std::setfill(' ') << " | Abgelegte Karten anzeigen" << std::endl << std::endl;
		std::cout << "Von welchem Stapel soll gezogen werden? ";

		std::cin >> cStack;
	

		switch (cStack) {
			case 1: { /*Ablagestapel*/
				if (Number == "!!") {
					std::cout << std::endl << "Diese Karte kann nicht gezogen werden!" << std::endl << std::endl;
					waitForEnter();
					cStack = -1;
				}
				else if (Number == "--") {
					std::cout << std::endl << "Karte kann nicht gezogen werden! Stapel ist leer!" << std::endl << std::endl;
					waitForEnter();
					cStack = -1;
				}
				else {
					p.setCard(10, dCards.top());
					dCards.pop();
				}
				break;
			}
			case 2: { /*Neuer Kartenstoß*/
				p.setCard(10, pullCard(AllCards));
				break;
			}
			case 3: { /*Abgelegte Karten anzeigen*/
				showDownCards(Players,Phases);
				break;
			}
			default: {
				cStack = 0;
				break;
			}
		}
	} while (cStack <= 0 || cStack > 2);

	return p;
}

int getCommand(Player p, std::vector<Phase> Phases, bool x){
	bool End = checkEnd(p);

	std::cout << std::endl << " 1 | Karten sortieren" << std::endl;
	if (End)
		std::cout << " 2 | Runde beenden" << std::endl;
	else
		std::cout << " 2 | Karte auf Ablagestapel legen (Zug beenden)" << std::endl;

	std::cout << " 3 | Phasen der Spieler anzeigen" << std::endl;
	std::cout << " 4 | Punkte der Spieler anzeigen" << std::endl;
	std::cout << " 5 | Abgelegte Karten anzeigen" << std::endl;

	if (!End) {
		if (p.getPhaseComplete())
			std::cout << " 6 | abgelegte Karten erweitern" << std::endl;
		else
			std::cout << " 6 | Karten ablegen" << std::endl;
	}
	std::cout << " 7 | Spiel speichern" << std::endl;
	std::cout << " 8 | zur" << (char)129 << "ck zum Hauptmen" << (char)129 << std::endl;

	std::cout << std::endl << "Auswahl: ";
	int command = 0;

	if(!x)
		std::cin >> command;
	return command;
}

bool checkEnd(Player p){
	int CCount = 0;

	for (int i = 0; i < 11; i++) {
		if (p.getCard(i).getValue() != 0)
			CCount++;
	}

	if (CCount <= 1)
		return true;
	else
		return false;
}

Player swapCards(Player p, std::vector<Phase> Phases){
	int Card1 = 15, Card2 = 15;
	while (Card1 > 11 || Card1 < 0) {
		clear();
		playerCards(p, Phases,true);

		std::cout << "Welche Karten sollen miteinander getauscht werden? (zum Abbrechen 0 eingeben)" << std::endl;
		std::cout << "Karte 1: ";
		std::cin >> Card1;
	}

	while ((Card2 > 11 || Card2 < 0) && Card1 != 0) {
		clear();
		playerCards(p, Phases,true);

		std::cout << "Welche Karten sollen miteinander getauscht werden? (zum Abbrechen 0 eingeben)" << std::endl;
		std::cout << "Karte 1: " << Card1 << std::endl;
		std::cout << "Karte 2: ";
		std::cin >> Card2;
	}
	if (Card1 != 0 && Card2 != 0) {
		Card1--;
		Card2--;

		Card temp = p.getCard(Card1);
		p.setCard(Card1, p.getCard(Card2));
		p.setCard(Card2, temp);
	}
	
	return p;
}

void expandDownCards(Player& player, std::vector<Player>& p, std::vector<Phase> Phases) {
	int SecPlayer = 0;
	int SecPart = 0;
	int SecCard = 0;

	/*Spieler auswahl*/
	do {
		clear();
		playerCards(player, Phases);
		std::cout << std::endl;
		showDownCards(p, Phases, true, true, false);

		std::cout << "Bei welchem Spieler willst du eine Karte ablegen? (zum Abbrechen 0 eingeben) ";
		std::cin >> SecPlayer;
		if (SecPlayer == 0)
			return;
	} while (SecPlayer < 1 || SecPlayer > p.size() || p[SecPlayer - 1].getPhaseComplete() == false);
	
	SecPlayer--;

	/*Teil auswahl*/
	if (Phases[p[SecPlayer].getPhase() - 1].getParts() > 1) {
		do {
			clear();
			playerCards(player, Phases);
			std::cout << std::endl;
			std::vector<std::vector<Card>> Cards = p[SecPlayer].getDownCards();

			for (int k = 0; k < Phases[p[SecPlayer].getPhase() - 1].getParts(); k++) {
				std::cout << " " << k + 1 << " | ";

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
			}
			std::cout << std::endl << "Welchem Teil m" << (char)148 << "chtest du eine Karte hinzuf" << (char)129 << "gen? (zum Abbrechen 0 eingeben) ";
			std::cin >> SecPart;

			if (SecPart == 0)
				return;
		} while (SecPart < 1 || SecPart > Phases[p[SecPlayer].getPhase() - 1].getParts());
		SecPart--;
	}
	else
		SecPart = 0;

	/*Karte auswahl*/
	do {
		clear();
		playerCards(player, Phases, true);
		std::cout << "Welche Karte soll diesem Teil hinzugef" << (char)129 << "gt werden? (zum Abbrechen 0 eingeben) ";
		std::cin >> SecCard;

		if (SecCard == 0)
			return;
	} while (SecCard < 0 || SecCard > 12 || player.getCard(SecCard - 1).getValue() == 0);

	SecCard--;

	std::cout << std::endl;

	std::vector<Card> Part = p[SecPlayer].getDownCards()[SecPart];

	/*Letzte Stelle finden*/
	int ix = Part.size();

	switch (Phases[p[SecPlayer].getPhase() - 1].getPartType(SecPart)) {
		case 1: {
			/*Überprüft ob erste Karte des Teils ein Jolly ist, damit beim weiteren ausführen keine fehler passieren*/
			int CC = 0;
			while (Part[CC].getValue() == 13)
				CC++;

			/*Überprüft ob Karte den selbenen Zahlenwert wie die erste Karte aus diesem Teil*/
			if (Part[CC].getValue() == player.getCard(SecCard).getValue() || player.getCard(SecCard).getValue() == 13) {
				p[SecPlayer].addDownCard(player.getCard(SecCard), SecPart);
				player.setCard(SecCard, Card(0, "-"));
			}
			else
				std::cout << "Karte passt nicht dazu!" << std::endl << std::endl;
			break;
		}
		case 2: {
			/*Überprüft ob erste Karte des Teils ein Jolly ist, damit beim weiteren ausführen keine fehler passieren*/
			int CC = 0;
			while (Part[CC].getValue() == 13)
				CC++;

			/*Überprüft ob Karte den selbenen Zahlenwert wie die erste Karte aus diesem Teil*/
			if (Part[CC].getColor() == player.getCard(SecCard).getColor() || player.getCard(SecCard).getValue() == 13) {
				p[SecPlayer].addDownCard(player.getCard(SecCard), SecPart);
				player.setCard(SecCard, Card(0, "-"));
			}
			else
				std::cout << "Karte passt nicht dazu!" << std::endl;
			break;
		}
		case 3: {
			int PlaceSlot = 0;
			int SetCard = 0;
			int CC = 0;
			int Direction = 0;
			int Cmin = 0;
			int Cmax = 0;
			bool worked = false;

			/*Wenn im Teil kein Platz mehr ist*/
			if (ix == 12) {
				std::cout << "In diesem Teil kann keine weitere Karte angelegt werden!" << std::endl << std::endl;
				break;
			}

			/*Abgelegt Richtung rausfinden*/
			for (int a = 0; a < ix; a++) {
				if (SetCard <= 0) {
					if (Part[a].getValue() == 13)
						continue;
					else {
						SetCard = Part[a].getValue();
						continue;
					}
				}
				else {
					if (Part[a].getValue() == 13) {
						CC++;
						continue;
					}
					else if (Part[a].getValue() > SetCard) { /*Part[a].getValue() == SetCard + 1 + CC*/
						Direction = 1;
						Cmin = SetCard + CC + 1 - a;
						Cmax = Cmin + ix - 1;
						break;
					}
					else if (Part[a].getValue() < SetCard) { /*Part[a].getValue() == SetCard - 1 - CC*/
						Direction = 2;
						Cmax = SetCard + CC + 1 - a;
						Cmin = Cmax - ix + 1;
						break;
					}
					else {
						std::cout << "FEHLER" << std::endl;
						break;
					}
				}
			}

			/*Jolly anlegen*/
			if (player.getCard(SecCard).getValue() == 13) {
				if (Cmin == 1 && Direction == 1) {
					p[SecPlayer].addDownCard(player.getCard(SecCard), SecPart);
				}
				else if (Cmax == 12 && Direction == 2) {
					std::vector<Card> tmp;

					tmp.push_back(player.getCard(SecCard));

					for (int k = 0; k < Part.size(); k++) {
						tmp.push_back(Part[k]);
					}

					p[SecPlayer].changeDownCardPart(tmp, SecPart);
				}
				else {
					int SecEnd = 0;
					std::cout << "   1   |    2" << std::endl << " Links | Rechts" << std::endl;
					std::cout << std::endl << "An welchem Ende soll die Karte hinzugef" << (char)129 << "gt werden? ";
					while (SecEnd <= 0 || SecEnd > 2)
						std::cin >> SecEnd;

					if (SecEnd == 1) {
						std::vector<Card> tmp;

						tmp.push_back(player.getCard(SecCard));

						for (int k = 0; k < Part.size(); k++) {
							tmp.push_back(Part[k]);
						}

						p[SecPlayer].changeDownCardPart(tmp, SecPart);
					}
					else {
						p[SecPlayer].addDownCard(player.getCard(SecCard), SecPart);
					}
				}

				worked = true;
			}

			/*Anlegen am linken Ende*/
			else if ((Direction == 1 && Cmin - 1 == player.getCard(SecCard).getValue()) ||
				(Direction == 2 && Cmax + 1 == player.getCard(SecCard).getValue())) {

				std::vector<Card> tmp;

				tmp.push_back(player.getCard(SecCard));

				for (int k = 0; k < Part.size(); k++) {
					tmp.push_back(Part[k]);
				}

				p[SecPlayer].changeDownCardPart(tmp,SecPart);

				worked = true;
			}

			/*Anlegen am rechten Ende*/
			else if ((Direction == 1 && Cmax + 1 == player.getCard(SecCard).getValue()) ||
				     (Direction == 2 && Cmin - 1 == player.getCard(SecCard).getValue())) {
				
				p[SecPlayer].addDownCard(player.getCard(SecCard),SecPart);

				worked = true;
			}
						
			/*Karte passt nicht dazu*/
			else {
				std::cout << "Karte passt nicht!" << std::endl << std::endl;
			}

			/*Karte entfernen*/
			if (worked) {
				player.setCard(SecCard, Card(0, "-"));
			}
			break;
		}
		case 4: {
			int PlaceSlot = 0;
			int SetCard = 0;
			int CC = 0;
			int Direction = 0;
			int Cmin = 0;
			int Cmax = 0;
			bool worked = false;

			/*Wenn im Teil kein Platz mehr ist*/
			if (ix == 12) {
				std::cout << "In diesem Teil kann keine weitere Karte angelegt werden!" << std::endl;
				break;
			}

			bool breaker = false;

			/*Farbe überprüfen*/
			for (int i = 0; i < ix; i++) {
				if (Part[i].getValue() == 13)
					continue;
				else {
					if (Part[i].getColor() != player.getCard(SecCard).getColor()) {
						breaker = true;
						break;
					}
						
				}
			}

			if (!breaker) {
				/*Abgelegt Richtung rausfinden*/
				for (int a = 0; a < ix; a++) {
					if (SetCard <= 0) {
						if (Part[a].getValue() == 13)
							continue;
						else {
							SetCard = Part[a].getValue();
							continue;
						}
					}
					else {
						if (Part[a].getValue() == 13) {
							CC++;
							continue;
						}
						else if (Part[a].getValue() > SetCard) { /*Part[a].getValue() == SetCard + 1 + CC*/
							Direction = 1;
							Cmin = SetCard + CC + 1 - a;
							Cmax = Cmin + ix - 1;
							break;
						}
						else if (Part[a].getValue() < SetCard) { /*Part[a].getValue() == SetCard - 1 - CC*/
							Direction = 2;
							Cmax = SetCard + CC + 1 - a;
							Cmin = Cmax - ix + 1;
							break;
						}
						else {
							std::cout << "FEHLER" << std::endl;
							break;
						}
					}
				}

				/*Anlegen am linken Ende*/
				if ((Direction == 1 && Cmin - 1 == player.getCard(SecCard).getValue()) ||
					(Direction == 2 && Cmax + 1 == player.getCard(SecCard).getValue())) {

					std::vector<Card> tmp;

					tmp.push_back(player.getCard(SecCard));

					for (int k = 0; k < Part.size(); k++) {
						tmp.push_back(Part[k]);
					}

					p[SecPlayer].changeDownCardPart(tmp, SecPart);

					worked = true;
				}

				/*Anlegen am rechten Ende*/
				else if ((Direction == 1 && Cmax + 1 == player.getCard(SecCard).getValue()) ||
					(Direction == 2 && Cmin - 1 == player.getCard(SecCard).getValue())) {

					p[SecPlayer].addDownCard(player.getCard(SecCard), SecPart);

					worked = true;
				}

				/*Jolly anlegen*/
				else if (player.getCard(SecCard).getValue() == 13) {
					if (Cmin == 1 && Direction == 1) {
						p[SecPlayer].addDownCard(player.getCard(SecCard), SecPart);
					}
					else if (Cmax == 12 && Direction == 2) {
						std::vector<Card> tmp;

						tmp.push_back(player.getCard(SecCard));

						for (int k = 0; k < Part.size(); k++) {
							tmp.push_back(Part[k]);
						}

						p[SecPlayer].changeDownCardPart(tmp, SecPart);
					}
					else {
						int SecEnd = 0;
						std::cout << std::endl << "   1   |    2" << std::endl << " Links | Rechts" << std::endl;
						std::cout << std::endl << "An welchem Ende soll die Karte hinzugefügt werden? ";
						while (SecEnd <= 0 || SecEnd > 2)
							std::cin >> SecEnd;

						if (SecEnd == 1) {
							std::vector<Card> tmp;

							tmp.push_back(player.getCard(SecCard));

							for (int k = 0; k < Part.size(); k++) {
								tmp.push_back(Part[k]);
							}

							p[SecPlayer].changeDownCardPart(tmp, SecPart);
						}
						else {
							p[SecPlayer].addDownCard(player.getCard(SecCard), SecPart);
						}
					}

					worked = true;
				}

				/*Karte passt nicht dazu*/
				else {
					std::cout << "Karte passt nicht!" << std::endl;
				}
			}

			/*Karte entfernen*/
			if (worked) {
				player.setCard(SecCard, Card(0, "-"));
			}
			break;
		}
		default: {
			std::cout << "Diese Art eines Teils exitstiert nicht!" << std::endl;
		}
	}
}

void finishPhase(Player& p, std::vector<Phase> Phases) {
	std::vector<int> CardPlaces;
	std::vector<std::vector<Card>> Parts;
	int Error = 0;

	clear();
	playerCards(p, Phases, true);

	for (int i = 0; i < Phases[p.getPhase() - 1].getParts(); i++) {
		std::cout << "Geben Sie " << Phases[p.getPhase() - 1].getPartLength(i);
		std::cout << " Karten " << PhaseTypeName(Phases[p.getPhase() - 1].getPartType(i) - 1) << " (zum Abbrechen 0 eingeben)" << std::endl << std::endl;

		for (int j = 0; j < Phases[p.getPhase() - 1].getPartLength(i); j++) {
			int CN = 0;

			while (CN > 12 || CN < 1) {
				std::cout << "Karte " << j + 1 << ": ";
				std::cin >> CN;
				CardPlaces.push_back(CN);
				if (CN == 0)
					return;
			}
		}
		std::cout << std::endl;
	}

	int counter = 0;

	for (int i = 0; i < Phases[p.getPhase() - 1].getParts(); i++) {
		std::vector<Card> tmp;
		tmp.clear();
		for (int j = 0; j < Phases[p.getPhase() - 1].getPartLength(i); j++) {
			tmp.push_back(p.getCard(CardPlaces[counter] - 1));
			counter++;
		}
		Parts.push_back(tmp);
	}

	/*Überprüft ob eine Karte doppelt angegeben wurde*/
	int size = CardPlaces.size();

	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (CardPlaces[i] == CardPlaces[j]) {
				Error = 1;
				break;
			}
		}
		if (Error)
			break;
	}

	/*Überprüft ob Phase korrekt abgelegt wurde*/
	for (int i = 0; i < Phases[p.getPhase() - 1].getParts(); i++) {
		if (!Error)
			Error = checkPhase(Phases[p.getPhase() - 1].getPartType(i), Parts[i]);

		if (Error) {
			/*Überprüfung der Fehlercodes*/
			switch (Error) {
				case 1: {
					std::cout << "Fehler: 2 oder mehr Karten wurden doppelt abgelegt!" << std::endl << std::endl;
					break;
				}
				case 2: {
					std::cout << "Fehler: Phase beinhaltet falsche Karten!" << std::endl << std::endl;
					break;
				}
				case 3: {
					std::cout << "Fehler: Kartenteil besteht aus zu vielen Jollys!" << std::endl << std::endl;
					break;
				}
				case 4: {
					std::cout << "Fehler: In den abgelegten Karten befindet sich ein Aussetzer!" << std::endl << std::endl;
					break;
				}
			}
			waitForEnter();
			break;
		}
	}

	if (Error)
		Parts.clear();
	else {
		for (int i = 0; i < Phases[p.getPhase() - 1].getParts(); i++)
			p.addDownCardPart(Parts[i]);
		p.downThisRound = true;

		for (int i = 0; i < CardPlaces.size(); i++) {
			p.setCard(CardPlaces[i] - 1, Card(0, "-"));
		}
	}
	std::cout << std::endl;
}

int checkPhase(int Type, std::vector<Card> Cards){
	switch (Type) {
		case 1: { /* Gleiche Zahl */
			int JC = 0;

			for (int i = 0; i < Cards.size(); i++) {
				if (Cards[i].getValue() == 13)
					JC++;

				if (Cards[i].getValue() == 14)
					return 4;
			}

			/*Überprüft ob zu viele Jollys vorhanden sind*/
			if (JC >= Cards.size())
				return 3;
			else {
				int Number = 0;

				for (int i = 0; i < Cards.size(); i++) {
					if (Cards[i].getValue() == 13)
						continue;
					else if (Number == 0)
						Number = Cards[i].getValue();
					else if (Number != Cards[i].getValue())
						return 1;
				}
			}
			return 0;
			break;
		}
		case 2: { /* Gleiche Farbe */
			int JC = 0;

			for (int i = 0; i < Cards.size(); i++) {
				if (Cards[i].getValue() == 13)
					JC++;

				if (Cards[i].getValue() == 14)
					return 4;
			}

			/*Überprüft ob zu viele Jollys vorhanden sind*/
			if (JC >= Cards.size())
				return 3;
			else {
				std::string Color = "";

				for (int i = 0; i < Cards.size(); i++) {
					if (Cards[i].getValue() == 13)
						continue;
					else if (Color == "")
						Color = Cards[i].getColor();
					else if (Color != Cards[i].getColor())
						return 1;
				}
			}
			return 0;
			break;
		}
		case 3: { /* Zahlenfolge */
			int JC = 0;

			for (int i = 0; i < Cards.size(); i++) {
				if (Cards[i].getValue() == 13)
					JC++;

				if (Cards[i].getValue() == 14)
					return 4;
			}

			/*Überprüft ob zu viele Jollys vorhanden sind*/
			if (JC >= Cards.size() - 1)
				return 3;

			int CardNumber[2] = { 0, 0 };
			int Direction = 0;

			for (int i = 0; i < Cards.size(); i++) {
				if (CardNumber[0] == 0 || CardNumber[1] == 0) {
					if (Cards[i].getValue() == 13)
						continue;
					else {
						CardNumber[0] = CardNumber[1] = Cards[i].getValue();
						continue;
					}
				}
				else if (Cards[i].getValue() == 13) {
					CardNumber[0]++;
					CardNumber[1]--;
					continue;
				}
				else {
					if (CardNumber[0] == Cards[i].getValue() - 1) {
						Direction = 1;
						break;
					}
					else if (CardNumber[1] == Cards[i].getValue() + 1) {
						Direction = 2;
						break;
					}
					else
						return 2;
				}
			}

			int CardNumberCheck = 0;
			for (int i = 0; i < Cards.size(); i++) {
				if (CardNumberCheck == 0) {
					if (Cards[i].getValue() == 13)
						continue;
					else {
						CardNumberCheck = Cards[i].getValue();
						continue;
					}
				}
				else if (Direction == 1) {
					if (Cards[i].getValue() == 13) {
						CardNumberCheck++;
						continue;
					}
					else if (CardNumberCheck == Cards[i].getValue() - 1) {
						CardNumberCheck++;
						continue;
					}
					else
						return 2;
				}
				else if (Direction == 2) {
					if (Cards[i].getValue() == 13) {
						CardNumberCheck--;
						continue;
					}
					else if (CardNumberCheck == Cards[i].getValue() + 1) {
						CardNumberCheck--;
						continue;
					}
					else
						return 2;
				}
			}
			return 0;
			break;
		}
		case 4: { /* Zahlenfolge einer Farbe */
			int JC = 0;

			for (int i = 0; i < Cards.size(); i++) {
				if (Cards[i].getValue() == 13)
					JC++;

				if (Cards[i].getValue() == 14)
					return 4;
			}

			/*Überprüft ob zu viele Jollys vorhanden sind*/
			if (JC >= Cards.size() - 1)
				return 3;

			int CardNumber[2] = { 0, 0 };
			int Direction = 0;

			for (int i = 0; i < Cards.size(); i++) {
				if (CardNumber[0] == 0 || CardNumber[1] == 0) {
					if (Cards[i].getValue() == 13)
						continue;
					else {
						CardNumber[0] = CardNumber[1] = Cards[i].getValue();
						continue;
					}
				}
				else if (Cards[i].getValue() == 13) {
					CardNumber[0]++;
					CardNumber[1]--;
					continue;
				}
				else {
					if (CardNumber[0] == Cards[i].getValue() - 1) {
						Direction = 1;
						break;
					}
					else if (CardNumber[1] == Cards[i].getValue() + 1) {
						Direction = 2;
						break;
					}
					else
						return 2;
				}
			}

			int CardNumberCheck = 0;
			for (int i = 0; i < Cards.size(); i++) {
				if (CardNumberCheck == 0) {
					if (Cards[i].getValue() == 13)
						continue;
					else {
						CardNumberCheck = Cards[i].getValue();
						continue;
					}
				}
				else if (Direction == 1) {
					if (Cards[i].getValue() == 13) {
						CardNumberCheck++;
						continue;
					}
					else if (CardNumberCheck == Cards[i].getValue() - 1) {
						CardNumberCheck++;
						continue;
					}
					else
						return 2;
				}
				else if (Direction == 2) {
					if (Cards[i].getValue() == 13) {
						CardNumberCheck--;
						continue;
					}
					else if (CardNumberCheck == Cards[i].getValue() + 1) {
						CardNumberCheck--;
						continue;
					}
					else
						return 2;
				}
			}

			std::string CColor = "";
			for (int i = 0; i < Cards.size(); i++) {
				if (CColor == "") {
					if (Cards[i].getValue() == 13)
						continue;
					else {
						CColor = Cards[i].getColor();
						continue;
					}
				}
				else {
					if (CColor != Cards[i].getColor()) {
						return 2;
					}
				}
			}
			return 0;
			break;
		}
	}
}

bool stopPlayer(Player player, std::vector<Player>& p, int AP, std::vector<Phase> Phases){
	int SP;
	do {
		clear();
		playerCards(player, Phases);

		std::cout << std::endl;

		for (int i = 0; i < p.size(); i++) {
			if (i == AP)
				continue;
			else
				std::cout << " " << i + 1 << " | " << p[i].getName() << std::endl;
		}

		std::cout << std::endl << "Welcher Spieler soll den Aussetzer erhalten? ";

		std::cin >> SP;
	} while (SP < 1 || SP > p.size() || SP - 1 == AP);

	if (p[SP - 1].stop()) {
		std::cout << "Spieler hat bereits eine Aussetzer erhalten!" << std::endl << std::endl;
		waitForEnter();
		return false;
	}
	else
		return true;
}

void endRound(std::vector<Player>& p, std::stack<Card>& dCards) {
	while (!dCards.empty()) {
		dCards.pop();
	}

	for (int i = 0; i < p.size(); i++) {
		if (p[i].getPhaseComplete())
			p[i].nextPhase();

		p[i].addScore();
	}
}

bool saveGame(int AP, std::vector<Player> p, std::stack<Card> dCards, int Round, std::vector<Phase> Phases, int PhaseSet = 1){
	std::string bs = ";";

	/*Datei öffnen*/
	std::fstream file("save.txt", std::ios::trunc | std::ios::out);

	if (!file)
		return false;
	else {
		file << p.size() << bs
			 << AP << bs
			 << Round << bs
			 << PhaseSet << bs
			 << std::endl;

		for (int i = 0; i < p.size(); i++) {
			file << p[i].getName() << bs
				<< p[i].getPhase() << bs
				<< p[i].getScore() << bs
				<< p[i].isStopped() << bs
				<< p[i].getPhaseComplete() << bs
				<< p[i].downThisRound << bs;
			for (int j = 0; j < 11; j++) {
				file << p[i].getCard(j).getColor() << bs
					<< p[i].getCard(j).getValue() << bs;
			}
			file << std::endl;
		}

		/*DiscardStack umlagern*/
		for (int i = 0; i < dCards.size(); i++) {
			file << dCards.top().getColor() << bs << dCards.top().getValue() << bs;
			dCards.pop();
		}

		file << std::endl;

		/*DownCards*/
		for (int i = 0; i < p.size(); i++) {
			if (p[i].getPhaseComplete() || p[i].downThisRound) {
				std::vector<std::vector<Card>> DC = p[i].getDownCards();

				for (int k = 0; k < Phases[p[i].getPhase() - 1].getParts(); k++) {
					int h = DC[k].size();

					for (int l = 0; l < h; l++) {
						file << DC[k][l].getColor() << bs << DC[k][l].getValue() << bs;
					}
					file << std::endl;
				}
			}
			else
				continue;
		}
	}

	file.close();

	return true;
}


