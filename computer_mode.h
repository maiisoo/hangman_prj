#pragma once

#include <string>
#include <set>

using namespace std;

char getNextGuess(const set<char>& previousGuesses, const string& secretWord);
