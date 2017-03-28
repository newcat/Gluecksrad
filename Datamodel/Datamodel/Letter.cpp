#include "Letter.h"
#include <ctype.h>

Letter::Letter() {
	letter_ = 0;
	visible_ = false;
}

Letter::Letter(char letter)
{
	letter_ = letter;
	visible_ = !isalpha(letter_);
}


Letter::~Letter(void)
{
}

bool Letter::isVisible() const {
	return visible_;
}

char Letter::getChar() const {
	return letter_;
}

void Letter::setVisible(bool visible){
	 visible_=visible;
}