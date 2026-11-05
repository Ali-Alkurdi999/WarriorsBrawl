#pragma once

#include <iostream>
#include <limits>


using namespace std;

namespace err
{
	void Error(int &Number, string Message)
	{
		while (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');

			cout << Message << endl;
			cin >> Number;
		}
	}
}