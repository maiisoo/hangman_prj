#include <iostream>
#include <set>

using namespace std;

void renderGame(const string &guessedWord, const string &badGuesses);
void displayFinalResult(bool won, const string &word, int totalScore);
void clearScreen();

void playAnimation(bool isLosing, const string &word);
void render(int incorrectGuess, set<char> previousGuesses, const string &secretWord);

string getDrawing(int incorrectGuess);
string getNextHangman();
string getNextStandingman();
