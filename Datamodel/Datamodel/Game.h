#pragma once

#include <string>
#include <vector>

#include "FortuneWheel.h"
#include "Player.h"
#include "Letter.h"

#define SENTENCE_COLUMNS	13
#define SENTENCE_ROWS		4
#define VOWEL_COST			1000

class Game
{
public:
	Game(void);
	~Game(void);

	Letter** getSentence(void) const;
	std::string getOutput(void) const;
	Player* getCurrentPlayer(void) const;
	std::vector<Player*>* getPlayers(void);

	void loadSentenceFromString(const std::string s);
	void addPlayer(const std::string name);
	void nextRound(void);

	FortuneWheelField spin(void);
	int guessConsonant(char c);
	int buyVowel(char c);
	bool guessSentence(const std::string sentence);

private:
	bool _spunWheel;
	std::vector<Player*> _players;
	std::vector<Player*>::iterator _playerIterator;
	std::string _output;
	Letter** _sentence;
	FortuneWheel _wheel;
	FortuneWheelField _lastSpinResult;
	void nextPlayer(void);

};
