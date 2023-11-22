// Author: Nathan Gessner
// Date  : 11-20-23
// Desc  : While loop hangman game, includes main menu and random api from vector list (or array)

#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <ctime>
using namespace std;


void wordGuessLogic(string&, string, string, int&, int&, bool&);
void letterGuessLogic(bool, int&, int, string, string, string&, string);

int main()
{
	string wordToGuess;
	string wordGuessed;
	string letterGuessed;
	string dashes;

	string letterPos;

	int maxGuesses = 5;
	int guessAmt = 0;
	int correctPos = 0;
	int menuSelection;
	
	bool endProgram = false;
	bool inputValidated = false;
	bool singlePlayer = false;
	bool multiPlayer = false;


#pragma region menu
	// MAIN MENU (optimize later)
	cout << "|----------------------------------------------------|" << endl;
	cout << "|" << setw(31) << "Hangman V3" << setw(53 - 31) << "|" << endl;
	
	// repair line: AUTHOR SECTION
	cout << "|" << setw(53) << "|";

	cout << endl << "|" << setw(37) << "Author: Nathan Gessner" << setw(53 - 37) << "|" << endl;

	cout << "|" << setw(53) << "|";
	cout << endl << "|----------------------------------------------------|" << endl;

	// DESCRIPTION SECTION:

	cout << "| Hangman V3 has multiplayer and singleplayer. Sing- |" << endl;
	cout << "| player picks a random word to guess, multiplayer's |" << endl;	
	cout << "| focus is for 2 people playing at the same computer.|" << endl;

	cout << "|" << setw(53) << "|";

	cout << endl << "|" << setw(31) << "have fun!!!" << setw (53 - 31) << "|" << endl;

	cout << "|" << setw(53) << "|";

	cout << endl << "|----------------------------------------------------|" << endl;

	cout << "|" << setw(53) << "|";
	// SELECTION SECTION:

	cout << endl << "|" << setw(20) << "1 - Multiplayer  " << setw (53 - 20) << "|" << endl;
	cout << "|" << setw(20) << "2 - Singleplayer " << setw(53 - 20) << "|" << endl;
	cout << "|" << setw(20) << "3 - Exit         " << setw(53 - 20) << "|" << endl;


	// border (adds about 3 more lines
	for (int i = 0; i < 2; i++)
	{
		cout << "|" << right << setw(53) << "|" << endl;
	}	
	cout << "|____________________________________________________|" << endl;

	// add logic later for if its not any of these numbers or selections (ex t3)
	cout << endl << "Enter your selection: ";
	cin >> menuSelection;
#pragma endregion menu

	// menu selection decider/setup
	if (menuSelection != 1 && menuSelection != 2 && menuSelection != 3)
	{
		while (!inputValidated)
		{			
			cout << "Not a valid option, try again: ";
			cin >> menuSelection;
			// moves the curson up one line and clears that output... theres tons of codes with purposes like this.
			cout << "\033[A\033[K"; 

			if (menuSelection == 1 || menuSelection == 2 || menuSelection == 3)
			{
				inputValidated = true;				
			}
		}
		inputValidated = false;
	}

	if (menuSelection == 1)
	{
		multiPlayer = true;
		system("CLS");
		// redundant code
		if (multiPlayer)
		{
			cout << "Insert a word for the player to guess: ";
			cin >> wordToGuess;

			system("CLS");			
		}
	}
	else if (menuSelection == 2)
	{
		singlePlayer = true;
		system("CLS");

		if (singlePlayer)
		{
			// could use vector here to expand during runtime
			string words[10] = {"Cat", "Green", "Elephant", "Harmony", "Computer", "Sunshine", "Butterfly", "Chocolate", "Adventure", "Serendipity"};

			// sets seed 
			srand(time(NULL));
			wordToGuess = words[rand() % 10];		
		}
	}
	else if (menuSelection == 3)
	{
		system("CLS");
		endProgram = true;

		cout << "thank you for playing!" << endl;
	}			
	if (multiPlayer || singlePlayer)
	{		
		for (int i = 0; i < wordToGuess.length(); i++)
		{
			// understand this better, look into nitty gritty
			if (wordToGuess.at(i) >= 'A' && wordToGuess.at(i) <= 'Z')
			{
				wordToGuess.at(i) = wordToGuess.at(i) + 32;
			}
			dashes += "- ";
		}
		cout << dashes << endl;

		while (!endProgram)
		{
			letterGuessLogic(inputValidated, maxGuesses, correctPos, letterGuessed, wordToGuess, dashes, letterPos);
			wordGuessLogic(dashes, wordGuessed, wordToGuess, maxGuesses, guessAmt, endProgram);
		}
	}			
}
void letterGuessLogic(bool inputValidated, int &maxGuesses, int correctPos, string letterGuessed, string wordToGuess, string &dashes, string letterPos)
{	
	cout << "You have " << maxGuesses << " guesses left. Guess a letter: ";
	cin >> letterGuessed;
	inputValidated = false;

	while (!inputValidated)
	{
		if (letterGuessed.length() != 1)
		{
			cout << "You did not enter a letter! Try again: ";
			cin >> letterGuessed;
			inputValidated = false;
		}
		else
		{		
			if (letterGuessed.at(0) >= 'A' && letterGuessed.at(0) <= 'Z')
			{
				letterGuessed.at(0) = letterGuessed.at(0) + 32;
			}
			for (int i = 0; i < wordToGuess.length(); i++)
			{

				if (letterGuessed.at(0) == wordToGuess.at(i))
				{
					dashes.at(i * 2) = wordToGuess.at(i);
					letterPos = to_string(i);

					correctPos++;

					if (correctPos == 1)
					{
						cout << "you guessed letter position ";
					}
					if (correctPos > 1)
					{
						cout << " and ";
					}
					cout << letterPos;
				}
			}
			if (correctPos > 0)
			{
			cout << " correct." << endl;
			}
			// breaks loops 
			inputValidated = true;
			correctPos = 0;
		}
	}	
}

void wordGuessLogic(string &dashes, string wordGuessed, string wordToGuess, int &maxGuesses, int &guessAmt, bool &endProgram)
{	
	cout << endl << dashes << endl;
	cout << "You have " << maxGuesses << " guesses left! Take a guess at the word: ";
	cin >> wordGuessed;
	guessAmt++;

	for (int i = 0; i < wordGuessed.length(); i++)
	{
		if (wordGuessed.at(i) >= 'A' && wordGuessed.at(i) <= 'Z')
		{
			wordGuessed.at(i) = wordGuessed.at(i) + 32;
		}
	}
	if (wordGuessed == wordToGuess)
	{
		// had to make a seperate for loop to not spam maxGuesses--
		for (int i = 0; i < wordGuessed.length(); i++)
		{
			dashes.at(i * 2) = wordGuessed.at(i);
		}
		cout << "you win!!! You guessed the word right in " << guessAmt << " guesses." << endl;
		endProgram = true;
	}
	else
	{
		maxGuesses--;
		if (maxGuesses == 0)
		{
			cout << "you lose!!! The word was " << wordToGuess << ". Bettter luck next time :(" << endl;
			endProgram = true;
		}
	}		
}