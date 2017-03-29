#include "Game.h"
#include <iostream>

int main() {


	Game g;
	g.addPlayer("Freddy");
	g.loadSentenceFromString(
		"*ICH SPIELE**"
		"**** DAS ****"
		"*GLUECKSRAD-*"
		"****SPIEL****"
	);

	std::cout << int(g.spin()) << std::endl;
	g.guessConsonant('D');
	g.getCurrentPlayer()->getBalance();
	g.guessSentence("ICH SPIELE DAS GLUECKSRADSPIEL");
	std::cout << g.getOutput();

	int x;
	std::cin >> x;

}