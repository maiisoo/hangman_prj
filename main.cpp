#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <fstream>
#include <algorithm>
#include <Windows.h>
#include <iomanip>
#include <set>
#include <conio.h>
#include <thread>
#include <chrono>
#include "computer_mode.h"
#include "util.h"
#include "draw.h"
#include "chooseWord.h"
#include "getHints.h"
#include "scoreUpdate.h"

using namespace std;

const int MAX_GUESSES = 7;
const int MAX_BAD_GUESSES = 7;
int mode = 0;
string level, topic;

string chooseWord(string level);
char readAGuess(int timeRestriction);
bool contains(const string &word, char guess);
void updateGuessedWord(string &guessedWord, const string &word, char guess);
string getLowerCaseString(const string &s);
void chooseMode();
void chooseLevelAndTopic();
int getTimeRestriction();
char getClue(string guessedWord, const string &word);
void gotoxy(short x, short y);

void initialize(int &wordLength, string &secretWord, int &incorrectGuess, set<char> &previousGuesses, bool &stop);
string getUserAnswer(char guess);
void update(char guess, const string &mask, int &incorrectGuess, set<char> &previousGuesses, string &secretWord, const int &maxAttempts, bool &stop);
bool isGoodMask(char guess, const string &mask, const string &secretWord);
int getUserWordLength();
void updateSecretWord(const string &mask, string &secretWord);
bool isAllDash(const std::string& s);
bool isAllNotDash(const std::string& s);

int main()
{
playAgain:
    chooseMode();

    // Computer_mode
    if (mode == 1){
        int wordLength;
        string secretWord;
        int incorrectGuess;
        set<char> previousGuesses;
        bool stop;
        int maxAttempts = getMaxAttempts();
        initialize(wordLength, secretWord, incorrectGuess, previousGuesses, stop);
        render(incorrectGuess, previousGuesses, secretWord);
        do {

            char guess = getNextGuess(previousGuesses, secretWord);
            if (guess == 0) {
                cout << "I give up, hang me" << endl;
                appendNewWord();
                return 0;
            }
            do {
                try {
                    string mask = getUserAnswer(guess);
                    update(guess, mask, incorrectGuess, previousGuesses, secretWord, maxAttempts, stop);
                    break;
                } catch (invalid_argument e) {
                    cout << "Invalid mask, try again" << endl;
                }
            } while (true);
            render(incorrectGuess, previousGuesses, secretWord);
        } while (!stop);
        if (incorrectGuess == maxAttempts){
            playAnimation(true, secretWord);
            appendNewWord();
        }
        else{
            playAnimation(false, secretWord);
        }
    }
    // Human_mode
    if (mode == 2){
        chooseLevelAndTopic();
        int timeRestriction = getTimeRestriction();
        int totalScore = 0;
        int cluelmt = clueLimit(level);
        int clueUsed = 0;
        string word = chooseWord(level, topic).first, word_def = chooseWord(level, topic).second;
        word = getLowerCaseString(word);
        string guessedWord = string(word.length(), '-');
        string badGuesses = "";
        set<char> closeLetters = getCloseSet(word);

        do
        {
            int countdown = timeRestriction;
            renderGame(guessedWord, badGuesses);
            reTry:
            char guess = readAGuess(countdown);
            if (guess == '1'){                          //Type '1' for a hints
                if (clueUsed < cluelmt){
                    guess = getClue(guessedWord,word);

                    clueUsed++;
                    if (clueUsed == cluelmt){
                        cout<<"[Alert] Be careful! You have ran out off clues. \n";
                        this_thread::sleep_for(1000ms);
                    }
                } else goto reTry;

            }
            if (guess == '2'){                          //Type '2' for word definition
                cout<<"Meaning: "<<word_def<<endl;
                this_thread::sleep_for(2000ms);
            }
            if (veryClose(guess,word,closeLetters)){
                cout<<"Letter "<<guess<<" are very close to the correct letter :)";
                this_thread::sleep_for(2000ms);
            }
            if (contains(word, guess)){
                updateGuessedWord(guessedWord, word, guess);
                updateCloseSet(guess,closeLetters);
                totalScore += pointAdd(level);
            }
            else
            {
                if (guess != '2')
                    badGuesses += guess;
                totalScore -= pointDec(level);
            }
        } while (badGuesses.length() < MAX_BAD_GUESSES && word != guessedWord);
        totalScore = totalScore*percent(clueUsed); updateScore(totalScore);
        displayFinalResult(badGuesses.length() < MAX_BAD_GUESSES, word,totalScore);
    }
    if (mode == 3){
        displayBestScore();
        this_thread::sleep_for(3000ms);
        goto playAgain;
    }
    //ask for again
    cout<<"Would you like to play again? <y/n> \n";
    char again;
    cin>>again;
    clearScreen();
    if (again == 'y')
        goto playAgain;
}

string getLowerCaseString(const string &s)
{
    string res = s;
    transform(s.begin(), s.end(), res.begin(), ::tolower);
    return res;
}

int getTimeRestriction(){
    cout<<"Enter time for guessing each turn (in seconds): ";
    int time;
    cin>>time;
    return time;
}

char readAGuess(int timeRestrict)
{
    int countdown = timeRestrict;
	char guess;
	while(countdown--){
		cout <<"\rTime remaining: " << setfill('0') << setw(2) << countdown;
		cout <<"\t Enter your guess: ";
		this_thread::sleep_for(1000ms);
		if(kbhit()){
			cout << endl;
			guess = getch();
			//cout<<guess;
			break;
		}
		guess = '0';
	}
	return tolower(guess);
}

bool contains(const string &word, char c)
{
    return (word.find_first_of(c) != string::npos);
}

void updateGuessedWord(string &guessedWord, const string &word, char guess)
{
    for (int i = word.length() - 1; i >= 0; i--)
    {
        if (word[i] == guess)
        {
            guessedWord[i] = guess;
        }
    }
}


void chooseMode(){
    system("color 87");
    cout<<"\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
    cout<<"\n\t\t\xdb\t\t\t\t\t\xdb\n\t\t\xdb\t\t\t\t\t\xdb";
    cout<<"\n\t\t\xdb\t=========MENU=========\t\t\xdb"<<endl;
 	cout<<"\t\t\xdb\t[1] Mode: Computer guesses\t\xdb"<<endl;
 	cout<<"\t\t\xdb\t[2] Mode: Human guesses\t\t\xdb"<<endl;
 	cout<<"\t\t\xdb\t[3] High Score\t\t\t\xdb"<<endl;
 	cout<<"\t\t\xdb\t\t\t\t\t\xdb\n\t\t\xdb\t\t\t\t\t\xdb";
 	cout<<"\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
    //gotoxy(1,15);
    cout<<"\n\n\t\tChoose a number to continue: "; cin >> mode;
    clearScreen();
}


void chooseLevelAndTopic(){
    clearScreen();
    cout<<"Choose difficulty: \n"
        <<"[1] EASY \n"
        <<"[2] MEDIUM \n"
        <<"[3] HARD \n"
        <<"Choose a number to continue: ";
    cin>>level;
    //clearScreen();
    cout<<"Choose topic: \n"
        <<"[1] PLANTS \n"
        <<"[2] ANIMALS \n"
        <<"[3] OTHERS \n"
        <<"Choose a number to continue: ";
    cin>>topic;
}

void initialize(int &wordLength, string &secretWord, int &incorrectGuess, set<char> &previousGuesses, bool &stop)
{
    wordLength = getUserWordLength();
    secretWord = string(wordLength, '-');
    incorrectGuess = 0;
    previousGuesses = set<char>();
    stop = false;
}

string getUserAnswer(char guess)
{
    string answer;
    cout << endl << "I guess " << guess << ", please enter your mask: ";
    cin >> answer;
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    return answer;
}

bool isGoodMask(char guess, const string &mask, const string &secretWord)
{
    if (mask.length() != secretWord.length())
        return false;
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-')
        {
            if (mask[i] != guess)
                return false;
            if (secretWord[i] != '-' && secretWord[i] != mask[i])
                return false;
        }
    return true;
}


void update(char guess, const string &mask, int &incorrectGuess, set<char> &previousGuesses, string &secretWord, const int &maxAttempts, bool &stop){
    if (!isGoodMask(guess, mask, secretWord))
        throw invalid_argument("mistake entering answer");
    previousGuesses.insert(guess);
    if (isAllDash(mask)){
        incorrectGuess++;
        if (incorrectGuess == maxAttempts)
            stop = true;
    }
    else
    {
        updateSecretWord(mask, secretWord);
        if (isAllNotDash(secretWord))
            stop = true;
    }
}

int getUserWordLength()
{
    int wordLength;
    cout << endl << "Enter your word length: ";
    cin >> wordLength;
    return wordLength;
}

void updateSecretWord(const string &mask, string &secretWord)
{
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-')
            secretWord[i] = mask[i];
}

void gotoxy(short x, short y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

