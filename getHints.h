#include <iostream>

using namespace std;

void gameHint();
int clueLimit(string level);
char getClue(string guessedWord, const string &word);
set<char> getCloseSet(const string &word);
void updateCloseSet(char guess, set<char> closeLetters);
bool veryClose(char guess, const string &word,  set<char> closeLetters);
