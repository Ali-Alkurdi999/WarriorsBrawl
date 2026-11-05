#pragma once

#include <cstdlib>

namespace RNG
{
	int RandomNumberGenerator(short From, short To)
	{
		int Number = 0;

		Number = rand() % (To - From + 1) + From;

		return Number;
	}

	char RandomCapitalLetter()
	{

		return char(RandomNumberGenerator(65, 90));

	}

	char RandomSmallLetter()
	{

		return char(RandomNumberGenerator(97, 122));

	}

	char RandomSpecialCharacter()
	{

		return char(RandomNumberGenerator(33, 47));

	}
	
	char RandomDigit()
	{

		return char(RandomNumberGenerator(48, 57));

	}

	char RandomCharacter()
	{
		char Array[4] = { 'A', 'B', 'C', 'D' };

		Array[0] = RandomCapitalLetter();
		Array[1] = RandomSmallLetter();
		Array[2] = RandomSpecialCharacter();
		Array[3] = RandomDigit();

		return Array[RandomNumberGenerator(0, 3)];
	}
}