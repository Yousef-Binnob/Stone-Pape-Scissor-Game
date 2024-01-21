#include <iostream>
#include<cstdlib>
using namespace std;

enum enGameChoice {stone = 1, paper = 2, scissors = 3};
enum enWinner {Player1 = 1, Computer = 2, NoWinner = 3};
struct stRoundInfo 
{
	short RoundNumber = 0;
	enGameChoice Player1Choice, ComputerChoice;
	enWinner RoundWinner;
	string WinnerName;
};
struct stGameResults
{
	short GameRounds = 0, PlayerWintimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	string GameWinner = "";
};

int ReadIntgerNumberInRange(int from, int to, string message)
{
	int number;

	cout << message;
	cin >> number;

	while (number < from || number > to)
	{
		cout << "Wrong number! Number must be between " << from << " and " << to << endl;
		cout << message;
		cin >> number;
	}
	return number;
}
int RandomNumber(int from, int to)
{
	//Function to generate a random number
	int RandNum = rand() % (to - from + 1) + from;
	return RandNum;
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void SetWinnerScreenColor(enWinner winner)
{
	switch (winner)
	{
	case Player1:
		system("color 2F");
		break;
	case Computer:
		cout << "\a";
		system("color 4F");
		break;
	default:
		system("color 6F");
		break;
	}
}
enWinner WhoWonTheRound(enGameChoice Player1Choice, enGameChoice Computerchoice)
{
	if (Player1Choice == Computerchoice)
		return enWinner::NoWinner;
	else if ((Player1Choice == enGameChoice::stone && Computerchoice == enGameChoice::paper)
		   ||(Player1Choice == enGameChoice::scissors && Computerchoice == enGameChoice::stone)
		   ||(Player1Choice == enGameChoice::paper && Computerchoice == enGameChoice::scissors))
		return enWinner::Computer;
	else
		return enWinner::Player1;
}
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return Player1;
	else if (Player1WinTimes < ComputerWinTimes)
		return Computer;
	else
		return NoWinner;
}
string GetChoice(enGameChoice choice)
{
	string Choice[3] = { "Stone", "Paper", "Scissors" };
	return Choice[choice - 1];
}
string GetWinnerName(enWinner winner)
{
	string WinnerName[3] = { "Player1", "Computer", "No Winner" };
	return WinnerName[winner - 1];
}
string Tabs(short NumberOfTabs)
{
	string tabs = "";
	for (int i = 1; i <= NumberOfTabs; i++)
	{
		tabs += "\t";
		//cout << tabs;
	}
	return tabs;
}
void ShowGameOver()
{
	cout << Tabs(4) << "____________________________________________\n\n";
	cout << Tabs(5) << "+++ G a m e  O v e r +++\n";
	cout << Tabs(4) << "____________________________________________\n\n";
}
void ShowRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n________Round[" << RoundInfo.RoundNumber << "]________\n"; 
	cout << "Player choice   : " << GetChoice(RoundInfo.Player1Choice) << endl;
	cout << "computer choice : " << GetChoice(RoundInfo.ComputerChoice) << endl;
	cout << "Round winner    : " << RoundInfo.WinnerName << endl;

	SetWinnerScreenColor(RoundInfo.RoundWinner);
}
void ShowGameResults(stGameResults Info)
{
	cout << Tabs(4) << "______________ [Game Results] ______________\n\n";
	cout << Tabs(4) << "Game rounds       : " << Info.GameRounds << endl;
	cout << Tabs(4) << "Player1 won times : " << Info.PlayerWintimes << endl;
	cout << Tabs(4) << "Computer won times: " << Info.ComputerWinTimes << endl;
	cout << Tabs(4) << "Draw times        : " << Info.DrawTimes << endl;
	cout << Tabs(4) << "Final winner      : " << GetWinnerName(WhoWonTheGame(Info.PlayerWintimes, Info.ComputerWinTimes)) << endl;
}
stGameResults PlayGame()
{
	stRoundInfo RoundInfo;
	stGameResults GameResults;
	GameResults.GameRounds = ReadIntgerNumberInRange(1, 10, "How many rounds do you want (1-10) ? ");

	for (short RoundNumber = 1; RoundNumber <= GameResults.GameRounds; RoundNumber++)
	{
		cout << "\nround[" << RoundNumber << "] begins:\n";

		RoundInfo.RoundNumber = RoundNumber;
		RoundInfo.Player1Choice = (enGameChoice)ReadIntgerNumberInRange(1, 3, "Your choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ");
		RoundInfo.ComputerChoice = (enGameChoice)RandomNumber(1, 3);
		RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo.Player1Choice, RoundInfo.ComputerChoice);
		RoundInfo.WinnerName = GetWinnerName(RoundInfo.RoundWinner);

		ShowRoundResults(RoundInfo);

		if (RoundInfo.RoundWinner == enWinner::Player1)
			GameResults.PlayerWintimes++;
		else if (RoundInfo.RoundWinner == enWinner::Computer)
			GameResults.ComputerWinTimes++;
		else
			GameResults.DrawTimes++;

	}
	return GameResults;
}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame();
		ShowGameOver();
		ShowGameResults(GameResults);
		cout << "\n\nDo you want to plar again (Y/N) ? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'y'|| PlayAgain == 'Y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}