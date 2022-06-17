#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

int generateRandomNumber(int min, int max)
{
    return rand() % (max-min) + min;
}

bool isCharInWord(char ch, string word)
{
    return (word.find_first_of(ch) != string::npos);
}

vector<string> readWordListFromFile(const string& filePath)
{
    vector<string> wordList;
    string word;
    ifstream wordFile(filePath);
    if (wordFile.is_open()) {
        while (wordFile >> word) {
            wordList.push_back(word);
        }
        wordFile.close();
        return wordList;
    } else {
        throw domain_error("Error: Unable to open vocabulary file " + filePath);
    }
}

string getSecretWord(){
    string secretWord;
    cout<<"Please tell me your secret word: ";
    cin>>secretWord;
    return secretWord;
}

void appendNewWord(){
    string newWord = getSecretWord();
    string filePath ="./word_list/data.txt";
    ofstream myFile;
    myFile.open(filePath, ios::app);
    if (!myFile.fail()){
        myFile << newWord <<"\n";
        myFile.close();
    }
    else{
        throw domain_error("Error: Unable to open vocabulary file " + filePath);
    }
}


bool isAllDash(const string& s)
{
    for (char c : s)
        if (c != '-') return false;
    return true;
}

bool isAllNotDash(const string& s)
{
    for (char c : s)
        if (c == '-') return false;
    return true;
}

int getMaxAttempts(){
    int attempts;
    cout<<"Enter number of attempts for the computer: ";
    cin>>attempts;
    return attempts;
}
