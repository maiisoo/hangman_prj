bool veryClosePrompt(string word, char guessedWord){
    set<char> closeLetters;
    for (int i=0; i<word.size(); i++){
        char ch = word[i];
        closeLetters.insert(ch+1);
        closeLetters.insert(ch);
        closeLetters.insert(ch-1);
    }
    if (closeLetters.find(guessedWord) != closeLetters.end()) return true;
    return false;
}
