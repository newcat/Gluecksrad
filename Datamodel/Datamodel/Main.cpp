#include "Game.h"
#include <iostream>

int main() {


	Game g;
	g.addPlayer("Freddy");
	g.nextRound();

	int res;
	while ((res = int(g.spin())) < 5) std::cout << res << std::endl;
	g.guessConsonant('S');
	g.getCurrentPlayer()->getBalance();
	std::cout << g.getOutput();

	int x;
	std::cin >> x;

}