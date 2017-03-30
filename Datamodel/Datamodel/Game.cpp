#include "Game.h"
#include "Sentences.h"

Game::Game(void)
{

	srand(time(NULL));

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
	return _output.str();
}

Player* Game::getCurrentPlayer(void) {

	if (_players.size() == 0) {
		_output << "No players added yet.\n";
		return NULL;
	}

	return *_playerIterator;

}

std::vector<Player*>* Game::getPlayers(void) {
	return &_players;
}

void Game::addPlayer(std::string name) {
	
	_players.push_back(new Player(name));

	if (_players.size() == 1)
		_playerIterator = _players.begin();

}

void Game::nextRound(void) {
	
	if (_players.size() == 0) {
		_output << "No players added yet.\n";
		return;
	}

	for (std::vector<Player*>::iterator it = _players.begin();
		it != _players.end(); it++) {
			(*it)->reset();
	}
	_playerIterator = _players.begin();
	_spunWheel = false;

	loadSentenceFromString(all_sentences[rand() % SENTENCE_COUNT]);

}

FortuneWheelField Game::spin(void) {

	if (_spunWheel) {
		_output << "Wheel has already been spun this round.\n";
		return FortuneWheelField::INVALID;
	}

	_lastSpinResult = _wheel.spin();
	_spunWheel = true;
	
	Player* p = getCurrentPlayer();

	if (_lastSpinResult == FortuneWheelField::BANKRUPT) {
		p->setBalance(0);
		_output << p->getName() << " just lost all his money :(\n";
		nextPlayer();
	} else if (_lastSpinResult == FortuneWheelField::EXTRASPIN) {		
		p->setExtraSpins(p->getExtraSpins() + 1);
		_output << p->getName() << " got an extra spin (" <<
			p->getExtraSpins() << " total).\n";
		_spunWheel = false;
	} else if (_lastSpinResult == FortuneWheelField::SKIP) {
		nextPlayer();
	}

	return _lastSpinResult;

}

int Game::guessConsonant(char c) {

	if (_players.size() == 0) {
		_output << "No players added yet.\n";
		return 0;
	}

	if (!_spunWheel) {
		_output << "You have to spin the wheel first.\n";
		return 0;
	}

	if (islower(c))
		c = toupper(c);

	if (!isalpha(c) || isVowel(c)) {
		_output << "The char must be valid and not a vowel.\n";
		return 0;
	}

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
	_output << '\'' << c << "' was revealed " << hits << " times.\n";
	_output << p->getName() << " won " << hits * int(_lastSpinResult) << "$.\n";

	_spunWheel = false;

	if (onlyVowelsRemaining())
		_output << "Only vowels remaining.\n";

	if (hits == 0)
		nextPlayer();

	return hits;

}

int Game::buyVowel(char c) {

	if (_players.size() == 0) {
		_output << "No players added yet.\n";
		return 0;
	}

	if (!_spunWheel) {
		_output << "You have to spin the wheel first.\n";
		return 0;
	}

	if (islower(c))
		c = toupper(c);

	if (!isalpha(c) || !isVowel(c)) {
		_output << "The char must be valid and a vowel.\n";
		return 0;
	}

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
	_output << p->getName() << " bought the vowel '" << c << "' for " << VOWEL_COST << "$.\n";
	_output << '\'' << c << "' was revealed " << hits << " times.\n";
	
	if (onlyVowelsRemaining())
		_output << "Only vowels remaining.\n";

	if (hits == 0)
		nextPlayer();

	return hits;

}

bool Game::guessSentence(const std::string sentence) {
	
	if (_players.size() == 0) {
		_output << "No players added yet.\n";
		return false;
	}

	if (!_spunWheel) {
		_output << "You have to spin the wheel first.\n";
		return false;
	}

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
		_output << getCurrentPlayer()->getName() << " guessed the sentence correctly.\n";
		nextRound();
		return true;

	} else {

		(*_playerIterator)->setBalance(0);
		_output << getCurrentPlayer()->getName() << " made a bad guess.\n";
		nextPlayer();
		return false;
		
	}

}

void Game::nextPlayer(void) {

	if (_players.size() == 0) {
		_output << "No players added yet.\n";
		return;
	}

	_spunWheel = false;

	Player* p = getCurrentPlayer();
	if (p->getExtraSpins() > 0) {
		p->setExtraSpins(p->getExtraSpins() - 1);
		_output << p->getName() << " used an extra spin.\n" <<
			p->getExtraSpins() << " extra spins remaining.\n";
	} else {
		_playerIterator++;
		if (_playerIterator == _players.end())
			_playerIterator = _players.begin();
		_output << "It's " + getCurrentPlayer()->getName() << "'s turn.\n";
	}
	
}

void Game::loadSentenceFromString(std::string s) {

	if (s.length() != SENTENCE_COLUMNS * SENTENCE_ROWS) {
		_output << "String has wrong length.\n";
		return;
	}

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

bool Game::onlyVowelsRemaining(void) const {

	for (int i = 0; i < SENTENCE_ROWS; i++) {
		for (int j = 0; j < SENTENCE_COLUMNS; j++) {
			if (!_sentence[i][j].isVisible()) {
				char c = _sentence[i][j].getChar();
				if (!isVowel(c) && c != '*')
					return false;
			}
		}
	}

	return true;

}

bool isVowel(char c) {
	return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}