#include "Game.h"
#include <iostream>

int main() {


	Game g;
	g.addPlayer("Freddy");
	g.loadSentenceFromString(
		" ICH SPIELE  "
		"     DAS     "
		" GLUECKSRAD- "
		"    SPIEL    "
	);

	std::cout << int(g.spin()) << std::endl;
	std::cout << g.guessConsonant('D') << std::endl;
	std::cout << g.getCurrentPlayer()->getBalance();

	int x;
	std::cin >> x;

}