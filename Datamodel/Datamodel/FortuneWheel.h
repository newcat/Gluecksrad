#pragma once

#include "FortuneWheelField.h"
#include <time.h>
#include <random>

class FortuneWheel
{
	public:
		FortuneWheel(void);
		~FortuneWheel(void);
		FortuneWheelField spin(void);
};

