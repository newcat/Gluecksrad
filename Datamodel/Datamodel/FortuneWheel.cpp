#include "FortuneWheel.h"

FortuneWheel::FortuneWheel(void)
{
	srand (time(NULL));
}


FortuneWheel::~FortuneWheel(void) { }


FortuneWheelField FortuneWheel::spin(void) {

	FortuneWheelField fieldValues[] = 
	{
		FortuneWheelField::BANKRUPT,
		FortuneWheelField::EXTRASPIN,
		FortuneWheelField::SKIP,
		FortuneWheelField::WIN50,
		FortuneWheelField::WIN75,
		FortuneWheelField::WIN100,
		FortuneWheelField::WIN150,
		FortuneWheelField::WIN200,
		FortuneWheelField::WIN250,
		FortuneWheelField::WIN300,
		FortuneWheelField::WIN500,
		FortuneWheelField::WIN1000,
		FortuneWheelField::WIN2500
	};

	int size = sizeof(fieldValues) / 4;
	int idx = rand() % size;
	return fieldValues[idx];
}
