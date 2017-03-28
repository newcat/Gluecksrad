#include "Game.h"
#include <exception>

Game::Game(void)
{

	_sentence = new Letter*[SENTENCE_ROWS];
	for (int i = 0; i < SENTENCE_ROWS; i++) {
		_sentence[i] = new Letter[SENTENCE_COLUMNS];
	}

	_spunWheel = false;

}

Game::~Game(void)
{

	_playerIterator = _players.begin();
	while (_playerIterator != _players.end()) {
		delete *_playerIterator;
	}
		
	for (int i = 0; i < SENTENCE_ROWS; i++) {
		delete[] _sentence[i];
	}
	delete[] _sentence;

}

Letter** Game::getSentence(void) const {
	return _sentence;
}

std::string Game::getOutput(void) const {
	return _output;
}

Player* Game::getCurrentPlayer(void) const {

	if (_players.size() == 0)
		throw std::exception("No players added yet.");

	return *_playerIterator;

}

std::vector<Player*>* Game::getPlayers(void) {
	return &_players;
}

void Game::addPlayer(const std::string name) {
	
	_players.push_back(new Player(name));

	if (_players.size() == 1)
		_playerIterator = _players.begin();

}

void Game::nextRound(void) {
	
	if (_players.size() == 0)
		throw std::exception("No players added yet.");

	for (std::vector<Player*>::iterator it = _players.begin();
		it != _players.end(); it++) {
			(*it)->reset();
	}
	_playerIterator = _players.begin();

}

FortuneWheelField Game::spin(void) {

	if (_spunWheel)
		throw std::exception("Wheel has already been spun this round.");

	_lastSpinResult = _wheel.spin();
	_spunWheel = true;
	
	if (_lastSpinResult == FortuneWheelField::BANKRUPT) {
		getCurrentPlayer()->setBalance(0);
		nextPlayer();
	} else if (_lastSpinResult == FortuneWheelField::EXTRASPIN) {
		Player* p = getCurrentPlayer();
		p->setExtraSpins(p->getExtraSpins() + 1);
	} else if (_lastSpinResult == FortuneWheelField::SKIP) {
		nextPlayer();
	}

	return _lastSpinResult;

}

int Game::guessConsonant(char c) {

	if (_players.size() == 0)
		throw std::exception("No players added yet.");

	if (!_spunWheel)
		throw std::exception("You have to spin the wheel first.");

	if (islower(c))
		c = toupper(c);

	if (!isalpha(c) || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
		throw std::exception("The char must be valid and not a vowel.");

	int hits = 0;
	for (int i = 0; i < SENTENCE_ROWS; i++) {
		for (int j = 0; j < SENTENCE_COLUMNS; j++) {
			if (_sentence[i][j].getChar() == c) {
				hits++;
				_sentence[i][j].setVisible(true);
			}
		}
	}

	Player* p = getCurrentPlayer();
	p->setBalance(p->getBalance() + hits * int(_lastSpinResult));

	if (hits == 0)
		nextPlayer();

	return hits;

}

int Game::buyVowel(char c) {

	if (_players.size() == 0)
		throw std::exception("No players added yet.");

	if (!_spunWheel)
		throw std::exception("You have to spin the wheel first.");

	if (islower(c))
		c = toupper(c);

	if (!isalpha(c) || !(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'))
		throw std::exception("The char must be valid and a vowel.");

	int hits = 0;
	for (int i = 0; i < SENTENCE_ROWS; i++) {
		for (int j = 0; j < SENTENCE_COLUMNS; j++) {
			if (_sentence[i][j].getChar() == c) {
				hits++;
				_sentence[i][j].setVisible(true);
			}
		}
	}

	Player* p = getCurrentPlayer();
	p->setBalance(p->getBalance() - VOWEL_COST);

	if (hits == 0)
		nextPlayer();

	return hits;

}

bool Game::guessSentence(const std::string sentence) {
	
	if (_players.size() == 0)
		throw std::exception("No players added yet.");

	if (!_spunWheel)
		throw std::exception("You have to spin the wheel first.");

	std::string solution;

	for (int i = 0; i < SENTENCE_ROWS; i++) {
		for (int j = 0; j < SENTENCE_COLUMNS; j++) {
			char c = _sentence[i][j].getChar();
			if (c != 0 && c != '-')
				solution += c;
		}
	}

	if (solution == sentence) {

		(*_playerIterator)->addBalanceToTotal();
		nextRound();
		return true;

	} else {

		(*_playerIterator)->setBalance(0);
		nextPlayer();
		return false;
		
	}

}

void Game::nextPlayer(void) {

	if (_players.size() == 0)
		throw std::exception("No players added yet.");

	_spunWheel = false;

	Player* p = getCurrentPlayer();
	if (p->getExtraSpins() > 0) {
		p->setExtraSpins(p->getExtraSpins() - 1);
	} else {
		_playerIterator++;
		if (_playerIterator == _players.end())
			_playerIterator = _players.begin();
	}
	
}

void Game::loadSentenceFromString(const std::string s) {

	if (s.length() != SENTENCE_COLUMNS * SENTENCE_ROWS)
		throw std::exception("String has wrong length.");

	for (int i = 0; i < SENTENCE_ROWS; i++) {
		for (int j = 0; j < SENTENCE_COLUMNS; j++) {

			char c = s[i * SENTENCE_COLUMNS + j];
			if (c == '*') {
				_sentence[i][j] = Letter();
			}
			else {
				_sentence[i][j] = Letter(c);
			}
			
		}
	}

}