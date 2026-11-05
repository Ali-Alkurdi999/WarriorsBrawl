#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <cmath> 
#include <cstdio>
#include <iomanip>
#include "RNG.h"
#include "err.h"

#pragma comment(lib, "winmm.lib")

using namespace std;

enum enCategories {Melee = 1, Ranged = 2, Magic = 3};
enum enDamageBonus {Common = 1, Rare = 2, Supreme = 3};

int Player = 0;

struct stComputer
{
	enCategories ComputerCategory = enCategories(RNG::RandomNumberGenerator(1, 3));
	enDamageBonus DamageBonus = enDamageBonus::Common;
	int HP = 999;
	int Damage = 0;
	string DamageBonusName = "";
	string Faint = "";
	int ComputerElementDamage = 0;
};
struct stPlayerId
{
	string Name = "";
	int HP = 100;
	char PlayerTier = 'F';
};
struct stGame
{
	stPlayerId PlayerId[100] = {};
	stComputer Computer = {};
	int RoundsNumber = 0;
	int PlayerDamage = 0;
	int ElementDamage = 0;
	string victoriousName = "Draw";
	string Faint = "";
	string DamageBonusName = "";
	int roundsPlayed = 0;
	bool GameOver = false;
	bool isFainted = false;
	string ElementFactorFor = "";
	enCategories Categories = enCategories::Melee;
	enDamageBonus DamageBonus = enDamageBonus::Common;
};
int AskForRoundsNumber()
{
	int RoundNumber = 0;

	do
	{
		printf("Please enter how many rounds you want to play form [ 1 to 20 ] : \n");
		cin >> RoundNumber;
		err::Error(RoundNumber, "How many ?!-_-");
	} while (RoundNumber < 1 || RoundNumber > 20);

	return RoundNumber;
}
string AskForPlayerName()
{
	string Name = "";
	cin.ignore();
	cout << "Please enter your Name :\n";
	getline(cin, Name);

	return Name;
}
int AskForPlayerAge()
{
	int Age = 0;
	do
	{
		printf("Please enter your age :\n");
		cin >> Age;
		err::Error(Age, "InValid kiddo, type again :");
	} while (Age < 1 || Age > 120);

	return Age;
}
void AskForCategory(enCategories &Categories)
{
	int Number = 0;
	do
	{
		cout << "Please enter your class [Melee = 1, Ranged = 2, Magic = 3] :\n";
		cin >> Number;
		err::Error(Number, "1, 2, 3, Ok budddy ?");
	} while (Number < 1 || Number > 3);

	Categories = enCategories(Number);
}
int RNGPlayerDamage()
{
	int Number = 0;

	Number  = RNG::RandomNumberGenerator(50, 100);

	return Number;
}
enDamageBonus RNGDamageBonus(string &DamageBonusName)
{
	int H = 0;

	H = RNG::RandomNumberGenerator(1, 10);

	if (H >= 1 && H <= 6)
	{
		DamageBonusName = "Common";
		return enDamageBonus::Common;
	}
	else if (H > 6 && H < 10)
	{
		DamageBonusName = "Rare";
		return enDamageBonus::Rare;
	}
	else
	{
		DamageBonusName = "Supreme";
		return enDamageBonus::Supreme;
	}
}
int ElementFactor(enCategories Player1, enCategories Player2)
{
	if (Player1 == Player2)
		return 0;

	if (Player1 == enCategories::Melee)
	{
		switch (Player2)
		{
		case enCategories::Magic:
			return 25;
		default:
			break;
		}
	}
	if (Player1 == enCategories::Magic)
	{
		switch (Player2)
		{
		case enCategories::Ranged:
			return 25;
		default:
			break;
		}
	}
	if (Player1 == enCategories::Ranged)
	{
		switch (Player2)
		{
		case enCategories::Melee:
			return 25;
		default:
			break;
		}
	}
	return -25;
}
bool Faint()
{
	int Number = 0;
	Number = RNG::RandomNumberGenerator(1, 5);

	return (Number == 5);
}
void RoundInfo(stGame &Game)
{
	
	Game.isFainted = Faint();

	if (Game.isFainted)
	{
		Game.Computer.Faint = "Fainted";
		Game.Computer.Damage = 0;
		Game.isFainted = false;
	}
	else
		Game.Computer.Faint = "Not Fainted";

	Game.PlayerId[Player].HP = Game.PlayerId[Player].HP - Game.Computer.Damage;

	Game.isFainted = Faint();

	if (Game.isFainted)
	{
		Game.Faint = "Fainted";
		Game.PlayerDamage = 0;
		Game.isFainted = false;
	}
	else
		Game.Faint = "Not Fainted";

	Game.Computer.HP = Game.Computer.HP - Game.PlayerDamage;


}
void SoundEffects(enDamageBonus DamageBonus, enDamageBonus DamageBonus2, int Player1HP, int ComputerHP)
{
	if (Player1HP <= 0 || ComputerHP <= 0)
		PlaySound(TEXT("TakeDown.wav"), NULL, SND_FILENAME || SND_SYNC);
	else if (DamageBonus == enDamageBonus::Supreme || DamageBonus2 == enDamageBonus::Supreme)
		PlaySound(TEXT("Hit3.wav"), NULL, SND_FILENAME || SND_SYNC);
	else if(DamageBonus == enDamageBonus::Rare || DamageBonus2 == enDamageBonus::Rare)
		PlaySound(TEXT("Hit2.wav"), NULL, SND_FILENAME || SND_SYNC);
	else if (DamageBonus == enDamageBonus::Common || DamageBonus2 == enDamageBonus::Common)
		PlaySound(TEXT("Hit1.wav"), NULL, SND_FILENAME || SND_SYNC);
}
void PrintRoundInfo(stGame Game, int i)
{
	printf("\tRound [ %d / %d ]\n", i + 1, Game.RoundsNumber);
	printf("----------------------------------------------------------------------------------\n");
	cout << "Player damage bonus : " << Game.DamageBonusName << "\t\tFaint info : " << Game.Faint << endl;
	cout << "Computer damage bonus : " << Game.Computer.DamageBonusName << "\t\tFaint info : " << Game.Computer.Faint << endl;
	printf("Player health : %03d\n", Game.PlayerId[Player].HP);
	printf("Computer health : %03d\n", Game.Computer.HP);
	printf("----------------------------------------------------------------------------------\n");
	
	system("pause");

}
string ElementFactorFavor(enCategories Player1, enCategories Computer)
{
	if (Player1 == Computer)
		return "Non";

	if (Player1 == enCategories::Melee)
	{
		switch (Computer)
		{
		case enCategories::Magic:
			return "Player";
		default:
			break;
		}
	}
	if (Player1 == enCategories::Magic)
	{
		switch (Computer)
		{
		case enCategories::Ranged:
			return "Player";
		default:
			break;
		}
	}
	if (Player1 == enCategories::Ranged)
	{
		switch (Computer)
		{
		case enCategories::Melee:
			return "Player";
		default:
			break;

		}
	}
	return "Computer";
}
void Round(stGame &Game, int i)
{
	Game.ElementFactorFor = ElementFactorFavor(Game.Categories, Game.Computer.ComputerCategory);

	Game.ElementDamage = ElementFactor(Game.Categories, Game.Computer.ComputerCategory);
	Game.DamageBonus = RNGDamageBonus(Game.DamageBonusName);
	Game.PlayerDamage = int(Game.DamageBonus) * RNGPlayerDamage() + Game.ElementDamage;

	Game.ElementDamage = ElementFactor(Game.Computer.ComputerCategory, Game.Categories);
	Game.Computer.DamageBonus = RNGDamageBonus(Game.Computer.DamageBonusName);
	Game.Computer.Damage = int(Game.Computer.DamageBonus) * RNGPlayerDamage() + Game.ElementDamage;

	RoundInfo(Game);

	SoundEffects(Game.DamageBonus, Game.Computer.DamageBonus, Game.PlayerId[Player].HP, Game.Computer.HP);
	
	PrintRoundInfo(Game, i);
	
}
void Finish(stGame &Game, int& i)
{
	if (Game.PlayerId[Player].HP <= 0 && Game.Computer.HP <= 0)
	{
		Game.victoriousName = "Draw";
		system("color 6F");
		i = 30;
	}

	else if (Game.PlayerId[Player].HP <= 0)
	{
		Game.victoriousName = "Computer";
		system("color 4F");
		i = 30;
	}
	else if (Game.Computer.HP <= 0)
	{
		Game.victoriousName = Game.PlayerId[Player].Name;
		system("color 2F");
		i = 30;
	}

}
void GamePlay(stGame &Game)
{
	for (int i = 0; i < Game.RoundsNumber; i++)
	{
		Game.roundsPlayed++;
		Round(Game, i);
		Finish(Game, i);
	}
}
void WinnerSound(stGame Game)
{
	if (Game.PlayerId[Player].HP > 0 && Game.Computer.HP <= 0)
		PlaySound(TEXT("Win.wav"), NULL, SND_FILENAME | SND_ASYNC);
	else
		PlaySound(TEXT("GameOver.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void Results(stGame Game)
{
	cout << endl << endl << "-------------------------------------------\n";
	printf("\tGame Over\n-------------------------------------------\n");
	cout << "Element factor is for : " << Game.ElementFactorFor << endl;
	cout << "Winner is : " << Game.victoriousName << endl;
	printf("Player HP : %03d\n", Game.PlayerId[Player].HP);
	printf("Computer HP : %03d\n", Game.Computer.HP);
	printf("Rounds played : %d out of %d\n", Game.roundsPlayed, Game.RoundsNumber);
	WinnerSound(Game);
}
void Status()
{
	stGame Game;
	Game.RoundsNumber = AskForRoundsNumber();
	Game.PlayerId[Player].Name = AskForPlayerName();
	Game.PlayerId[Player].HP = 999;
	
	AskForCategory(Game.Categories);
	
	GamePlay(Game);

	Results(Game);
}
void Resetscreen()
{
	system("cls");
	system("color 0F");
}
void PlayAgain()
{
	
	int Answer = 0;
	do
	{
		Resetscreen();
		Status();
		::Player++;
		printf("Do you want to play again? [Y = 1, No = Any]\n");
		cin >> Answer;
		err::Error(Answer, "Invalid, you want to play ? [Yes = 1, No = 0]");

	} while (Answer == 1);
}

int main()
{
	srand((unsigned)time(NULL));

	PlayAgain();
}