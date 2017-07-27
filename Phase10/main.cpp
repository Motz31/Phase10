#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "Card.h"
#include "Player.h"
#include "Display.h"
#include "Setup.h"
#include "Game.h"
#include "Phase.h"

using namespace std;

int main() {
	clear();
	int INPUT = 0;
	int PhaseSet = 0;
	int Autosave = 1;
	bool ActiveStoppers = true;
	unsigned int Round = 1;
	unsigned int ActivePlayer = 0;
	bool GameOver = false;
	bool RoundEnd = false;
	vector<Player> Players;
	vector<Card> AllCards;
	stack<Card> dCards;
	vector<Phase> Phases;

	do {
		showMM();
		cin >> INPUT;
		switch (INPUT) {
			case 1: /*Neues Spiel*/
			case 2: { /*Spiel Laden*/
				GameOver = false;
				RoundEnd = false;
				AllCards = generateCards(ActiveStoppers);
				if (INPUT == 2) {
					int LAP = 0, LRound = 1;
					std::vector<Player> LPlayers;
					std::stack<Card> LdCards;
					std::vector<Phase> LPhases;
					if (!loadGame(LAP, LPlayers, LdCards, LRound, LPhases))
						break;						
					ActivePlayer = LAP;
					Players = LPlayers;
					dCards = LdCards;
					Phases = LPhases;
				}
				else {
					Phases = createPhases(PhaseSet);
					Players = createPlayers();
				}
				
				while (!GameOver) {
					if (INPUT != 2) {
						Players = prepareRound(Players, AllCards);
						dCards.push(pullCard(AllCards));
						RoundStart(Round);
						ActivePlayer = (Round - 1) % Players.size();
					}
					int command = 0;
					bool RoundBeginn = true;
					while (!RoundEnd) {
						nextPlayer(Players[ActivePlayer].getName());
						if (Players[ActivePlayer].isStopped()) { /*Ausführung beim Laden eines Spielers nicht möglich, daher muss es auch nicht ausgeblendet werden bei laden eines Spiels*/
							stoppedText();
							dCards.push(Card(14, "!"));
							Players[ActivePlayer].Cstop();
						}
						else {
							if (INPUT != 2)
								Players[ActivePlayer] = pickCard(Players[ActivePlayer], Players, dCards, AllCards, Phases);
							
							INPUT = 0;
							command = 0;

							if (Autosave == 2 || (RoundBeginn && Autosave == 1)) {
								saveGame(ActivePlayer, Players, dCards, Round, Phases, PhaseSet);
								RoundBeginn = false;
							}
							do {
								clear();
								playerCards(Players[ActivePlayer],Phases);
								command = getCommand(Players[ActivePlayer], Phases);

								switch (command) {
									case 1: { /*Karten sortieren*/
										Players[ActivePlayer] = swapCards(Players[ActivePlayer], Phases);
										break;
									}
									case 2: { /* Zug/Runde beenden */
										if (checkEnd(Players[ActivePlayer])) {
											for (int i = 0; i < 11; i++) {
												Players[ActivePlayer].setCard(i,Card(0,"-"));
											}
										}
										else { /*Karte auf Ablagestapel legen*/
											int TCard = discardCard(Players[ActivePlayer],Phases);
											if (TCard == 0) {
												command = 0;
												break;
											}
											else {
												if (Players[ActivePlayer].getCard(TCard - 1).getValue() == 14) {
													if (!stopPlayer(Players[ActivePlayer], Players, ActivePlayer, Phases))
														command = 0;
													else
														Players[ActivePlayer].setCard(TCard - 1, Card(0, "-"));
												}
												else {
													dCards.push(Players[ActivePlayer].getCard(TCard - 1));
													Players[ActivePlayer].setCard(TCard - 1, Card(0, "-"));
												}

												if (command != 0) {
													for (int i = TCard; i <= 11; i++) {
														Players[ActivePlayer].setCard(i - 1, Players[ActivePlayer].getCard(i));
													}
													Players[ActivePlayer].setCard(10, Card(0, "-"));
												}
											}
										}
										break;
									}
									case 3: { /* Phasen der Spieler anzeigen */
										clear();
										playerCards(Players[ActivePlayer],Phases);
										PlayerPhases(Players, Phases);
										break;
									}
									case 4: { /* Phasen der Spieler anzeigen */
										clear();
										playerCards(Players[ActivePlayer],Phases);
										PlayerScores(Players);
										break;
									}
									case 5: { /* Abgelegte Karten anzeigen */
										clear();
										playerCards(Players[ActivePlayer],Phases);
										showDownCards(Players, Phases);
										break;
									}
									case 6: { /* Phase ablegen/erweitern */
										if (!checkEnd(Players[ActivePlayer])) {
											clear();
											playerCards(Players[ActivePlayer], Phases);

											if (Players[ActivePlayer].downThisRound)
												cout << endl << "Sie haben ihre Phase bereits abgelegt!" << endl << endl;
											else {
												if (Players[ActivePlayer].getPhaseComplete())
													expandDownCards(Players[ActivePlayer], Players, Phases);
												else
													finishPhase(Players[ActivePlayer], Phases);
											}
										}
										break;
									}
									case 7: { /*Spiel speichern*/
										if (!saveGame(ActivePlayer, Players, dCards, Round, Phases, PhaseSet))
											cout << endl << "Fehler: Datei konnte nicht gefunden oder geöffnet werden!" << endl << endl;
										else
											cout << endl << "Spiel wurde erfolgreich gespeichert!" << endl << endl;
										waitForEnter();
										break;
									}
									case 8: { /*Zum Haupt Menü*/
										break;
									}
								}
							} while (command != 2 && command != 8);
						}
						if (command != 8) {
							if (Players[ActivePlayer].getCardCount() >= 1) {
								if (Players[ActivePlayer].downThisRound) {
									Players[ActivePlayer].setPhaseComplete(true);
									Players[ActivePlayer].downThisRound = false;
								}

								if (ActivePlayer >= Players.size() - 1)
									ActivePlayer = 0;
								else
									ActivePlayer++;
							}
							else { /*Runde wird beendet*/
								bool BR = false;
								for (int i = 0; i < Players.size(); i++) {
									if (Players[i].getPhase() == 10 && Players[i].getPhaseComplete()) {
										for (int k = 0; k < Players.size(); k++) {
											Players[k].addScore();
										}
										endGame(Players);
										waitForEnter();
										BR = true;
										break;
									}
								}
								if (!BR) {
									endRound(Players, dCards);
									RoundEndScreen(Players[ActivePlayer], Players, Round, Phases);
									Round++;
									for (int i = 0; i < Players.size(); i++) {
										Players[i].resetPlayer();
									}
								}
								else {
									RoundEnd = true;
									GameOver = true;
									INPUT = 0;
								}
								break;
							}
						}
						else {
							GameOver = true;
							RoundEnd = true;
							INPUT = 0;
						}
					}
				}
				break;
			}
			case 3: {
				showInstructions();
				break;
			}
			case 4: { /*Einstellungen*/
				int _IN = -1;
				do {
					do {
						_IN = 0;
						showSettings(PhaseSet, ActiveStoppers, Autosave);

						cin >> _IN;
					} while (_IN < 0 || _IN > 4);

					switch (_IN) {
						case 1: {
							if (PhaseSet + 1 > 1)
								PhaseSet = 0;
							else
								PhaseSet++;
							break;
						}
						case 2: {
							ActiveStoppers = !ActiveStoppers;
							break;
						}
						case 3: {
							if (Autosave + 1 > 2)
								Autosave = 0;
							else
								Autosave++;
							break;
						}
						case 4: {
							break;
						}
					}
				} while (_IN != 4);
				INPUT = 0;
				break;
			}
			case 5: { /*Spiel beenden*/
				return 0;
				break;
			}
			default: {
				INPUT = 0;
			}
		}
	} while (INPUT != 4);
	return 0;
}