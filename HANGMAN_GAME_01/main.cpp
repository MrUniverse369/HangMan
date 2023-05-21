#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>

int playerLives = 3;
std::string playerGuess;
std::string answer;
std::string guessedLetters;
std::string wordToGuess;
std::vector<std::string> wordsToGuess;
std::vector<std::string>::iterator wordsToguessIter;
bool guessiscorrect = false;
bool gameOver = true;
bool inputValid = false;
void setUp();
void updateGameInternals();
void updateDisplay();
bool isGameOver(bool gameOver);
void guessedLettersInit();
bool isLetterGuessed(std::string& playerGuess, std::string& guessedLetters);
void clearScreen();
void validatePlayerInput(std::string playerGuess);
std::string getPlayerInput();

int main() {
	/*/simulate random number generation by using
  time as the seed number random number will
  be selected based on the seconds value of time*/
	srand(static_cast<unsigned int>(std::time(0)));

	setUp();
	guessedLettersInit();
	do
	{
		validatePlayerInput(getPlayerInput());
		updateGameInternals();
		updateDisplay();
	} while (!isGameOver(gameOver));
	system("pause");
	return EXIT_SUCCESS;
}

//start and display game rules
void setUp() {
	//initialise the container with words to be guessed
	wordsToGuess.push_back("LION");
	wordsToGuess.push_back("WATER");
	wordsToGuess.push_back("POKEMON");
	wordsToGuess.push_back("BATMAN");
	wordsToGuess.push_back("JOKER");
	wordsToGuess.push_back("WONDERWOMAN");

	wordsToguessIter = wordsToGuess.begin();

	/*randomize the wordtoguess vector using random
	shuffle this makes the word to guess different each time
	the game is started from compile time */
	std::random_shuffle(wordsToGuess.begin(), wordsToGuess.end());
	//pick a word for the player to guess from the randomised container
	wordToGuess = *wordsToguessIter;
	playerLives = 4;

	//start and display game rules 
	std::cout << "Welcome to hangman \nYour aim is to guess correctly all the letters in the word\nFail to do so, you shall be hung\n\n";
}

//Inialise usedLetters to be as big as the (word the player  is gusessing + 1) so when letters are being stored in there it never goes out of index
void guessedLettersInit()
{
	for (size_t i = 0; i < wordToGuess.length(); i++)
	{
		guessedLetters += " ";
	}

}

// cleans the screen 
void clearScreen()
{
	system("cls");
}

//This function returns true if the letter the player's Input has already been guessed 
bool isLetterGuessed(std::string& playerGuess, std::string& guessedLetters) {
	int i = 0;
	bool r = false;

	/*r = Input is a letter that has already been guessed

	whislt we have not reached the end of our guessed letter container and input is a letter that has not been guessed
	is false will continue to loop around guessed letters we do this to make sure we check every element of guessed
	letter to see if the input the user has put in has already been used
	*/

	while (i < guessedLetters.length() && r != true)
	{
		//isLetterGuessed = (playerGuess[0] == guessedLetters[i]) ? true : false;
		r = (playerGuess[0] == guessedLetters[i]) ? true : false;
		i++;
	}


	return r;
}

//The function checks to see if the input the user has entered is valid based on the conditions we set
void validatePlayerInput(std::string playerGuess)
{
	bool loopDone = true;
	bool isLetterGuessedvar = false;
	int i = 0;
	bool r;



	do
	{
		//This function returns true if the letter the player's Input has already been guessed 
		r = isLetterGuessed(playerGuess, guessedLetters);

		/*
		p = Player input is a  alhabtetical value
		q = user input is clean
		r = input is a letter that has already been guessed

		argumeant
		if player input is an alphabetical letter and  input is not
		a letter that has already been guessed then user input is clean

	  (p^¬r) -> q;

		*/
		if (!((playerGuess >= "A" && playerGuess <= "Z") && !r))
		{
			std::cout << "Input is  Invalid Try again \n";
			std::cout << "Please Pick a letter between A - Z that has not been already chosen \n";
			playerGuess = getPlayerInput();
			r = isLetterGuessed(playerGuess, guessedLetters);
		}

		/* do this while  !(p^¬q)*/
	} while (!((playerGuess >= "A" && playerGuess <= "Z") && !r));
}


//Reads the input the player types and returns it in upperCase
std::string getPlayerInput()
{
	// read user input 
	std::cin >> playerGuess[0];
	playerGuess = ::toupper(playerGuess[0]);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return playerGuess;
}

//This function updates the game based on playerInput
void updateGameInternals()
{
	//loop around until we have gone through every element of word to guess
	for (size_t i = 0; i < wordToGuess.length(); i++)
	{
		//if letter matches with player guess we set guessiscorrect to true to indicate that the player guess is correct 
		if (playerGuess[0] == wordToGuess[i])
		{
			//set correct guess to apear in the right order in used letters 
			guessedLetters[i] = playerGuess[0];
			guessiscorrect = true;
		}
	}
	//if loop is over and guess is incorrect take life 
	if (!guessiscorrect) playerLives = playerLives - 1;

	guessiscorrect = false;

	/*if the word to guess matches the letters our player has guessed esxcatly
	we indicated to the program that the game is over */
	gameOver = (wordToGuess == guessedLetters) ? true : false;
}

void updateDisplay()
{
	clearScreen();
	///prompt user to guess 
	std::cout << "LIVES:" << playerLives << "\n";
	std::cout << "Pick a letter from A-Z\n";
	std::cout << "So far you have guessed\n" << guessedLetters << "\n\n";
}

//lets us know when the game is over by returning or false to indicate that state of the game
bool isGameOver(bool gameOver)
{
	/*if the game is over and player lives is greater than 0 the player has won*/
	if (gameOver && playerLives > 0) std::cout << "You win\n";

	// if the players lives are less than 1 they have lost the game 
	if (playerLives < 1)
	{

		std::cout << "You have " << playerLives << " lives left you loose \n\n";
		gameOver = true;

	}

	return gameOver;

}

