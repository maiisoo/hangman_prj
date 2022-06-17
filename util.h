#pragma once

#include <vector>
#include <string>

using namespace std;

int generateRandomNumber(int min, int max);
bool isCharInWord(char ch, std::string word);
vector<string> readWordListFromFile(const string& filePath);
void appendNewWord();
bool isAllDash(const std::string& s);
bool isAllNotDash(const std::string& s);
int getMaxAttempts();
