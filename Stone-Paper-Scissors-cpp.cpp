#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

enum enGameChoice
{
	Stone = 1,
	Paper = 2,
	Scissors = 3
};

enum enWinner
{
	Player1 = 1,
	Computer = 2,
	Draw = 3
};

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults
{
	int GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";

};

short RandomNumber(short From, short To)
{
	return rand() % (To - From + 1) + From;
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
			return enWinner::Computer;
		break;
	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
			return enWinner::Computer;
		break;
	}
	return enWinner::Player1;
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes == ComputerWinTimes)
		return enWinner::Draw;
	else if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else
		return enWinner::Computer;
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1","Computer","No Winner" };
	return arrWinnerName[Winner - 1];
}

stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);
	return GameResults;
}

string ChoiceName(enGameChoice Choice)
{
	string arrChoiceName[3] = { "Stone","Paper","Scissors" };
	return arrChoiceName[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 0A");
		break;
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6F");
		break;
	}
}

enGameChoice ReadPlayerChoice()
{
	short Choice = 1;
	do
	{
		cout << "\nYour Choice : [1]:Stone , [2]:Paper , [3]:Scissors ? ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return enGameChoice(Choice);
}

enGameChoice GetComputerChoice()
{
	return enGameChoice(RandomNumber(1, 3));
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n_______________ Round [" << RoundInfo.RoundNumber << "] _______________\n\n";
	cout << "Player1  Choice : " << ChoiceName(RoundInfo.Player1Choice) << "\n";
	cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << "\n";
	cout << "Round Winner    : [" << RoundInfo.WinnerName << "] \n";
	cout << "\n_________________________________________\n\n";
	SetWinnerScreenColor(RoundInfo.Winner);
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\n\nRound [" << GameRound << "] begins :\n\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
		if (RoundInfo.Winner == enWinner::Player1)
			PlayerWinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;
		PrintRoundResults(RoundInfo);
	}
	return FillGameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i <= NumberOfTabs; i++)
		t = t + "\t";

	return t;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "__________________________________________________________________________________________\n\n";
	cout << Tabs(2) << "                                  +++ G A M E  O V E R +++                                \n";
	cout << Tabs(2) << "__________________________________________________________________________________________\n\n";

}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "_____________________________________[  Game Results  ]___________________________________\n\n";
	cout << Tabs(2) << "Game Rounds             : " << GameResults.GameRounds << "\n";
	cout << Tabs(2) << "Player 1 Won Times      : " << GameResults.Player1WinTimes << "\n";
	cout << Tabs(2) << "Computer Won Times      : " << GameResults.ComputerWinTimes << "\n";
	cout << Tabs(2) << "Draw Times              : " << GameResults.DrawTimes << "\n";
	cout << Tabs(2) << "Final Winner            : " << GameResults.WinnerName << "\n";
	cout << Tabs(2) << "__________________________________________________________________________________________\n";

	SetWinnerScreenColor(GameResults.GameWinner);
}

static short ReadHowManyRounds()
{
	short GameRounds = 1;
	do
	{
		cout << "How Many Rounds 1 to 10 ?\n";
		cin >> GameRounds;
	} while (GameRounds < 1 || GameRounds > 10);
	return GameRounds;
}

void ResetScreen()
{
	system("color 07");
	system("cls");
}

void StartGame()
{
	char playAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);
		cout << "\n" << Tabs(3) << "Do You Want To Play Again  ? Y/N? ";
		cin >> playAgain;
	} while (playAgain == 'y' || playAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;

}

