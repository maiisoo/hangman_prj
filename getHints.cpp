#include <iostream>
#include <set>

using namespace std;

void gameHint(){
    cout<<"Enter '1' if you want to have a letter revealed. (-10% per clue) \n"
        <<"Enter '2' if you want to see Vietnamese meaning \n"
        <<"EASY: 2 clues available. \n"
        <<"MEDIUM: 2 clues available. \n"
        <<"HARD: 3 clues available. \n\n";
};

int clueLimit(string level){
    if (level == "1") return 2;
    else if (level == "2") return 2;
    else if (level == "3") return 3;
}

char getClue(string guessedWord, const string &word){
    int i = 0;
    while (i <= word.size()){
        if (guessedWord[i]!=word[i]) return word[i];
        else i++;
    }
}

set<char> getCloseSet(const string &word){
    set<char> closeLetters;
    for (int i=0; i<word.size(); i++){
        char ch = word[i], pre = ch-1, pos = ch+1;
        if(word.find(pre) == string::npos) closeLetters.insert(pre);
        if(word.find(pos) == string::npos) closeLetters.insert(pos);
    }
    return closeLetters;
}

void updateCloseSet(char guess, set<char> closeLetters){
     if (closeLetters.find(guess) != closeLetters.end())
        closeLetters.erase(guess);
}

bool veryClose(char guess, const string &word,  set<char> closeLetters){                  // Check ky tu trong vong 1 don vi so voi ky tu can tim
    if (closeLetters.find(guess) != closeLetters.end()) return true;
    return false;
}
