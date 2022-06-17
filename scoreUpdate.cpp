#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <draw.h>
#include <iomanip>

using namespace std;

void updateScore(int totalScore) {
	ofstream writeFile;
	writeFile.open("highScore.txt",ios::app);
	if (!writeFile.fail()){
        writeFile<<"\n" << totalScore;
        writeFile.close();
    }
	else{
        throw domain_error("Error: Failed to open this file. ");
    }
}


vector<double> getTop10(){
    vector<double> top10(10,0), scoreData;
    ifstream myfile("highScore.txt");
    double score;
    if (myfile.is_open()){
        while (myfile>>score){
            scoreData.push_back(score);
        }
        myfile.close();
    }
    else {
        throw domain_error("Error: Failed to open this file. ");
    }
    sort(scoreData.begin(),scoreData.end(),greater<double>());
    for (int i = 0; i<scoreData.size(); i++){
        top10[i] = scoreData[i];
    }
    return top10;
}

void displayBestScore(){
    vector<double> top10 = getTop10();
 	cout<<"\t\t=====Ranking=====\t\t\t"<<endl;
    for (int i = 0; i<10; i++) cout<<setw(20)<<setfill(' ')<<i+1<<setw(5)<<": "<<top10[i]<<endl;
}

int pointAdd(string level){
    if (level == "1") return 5;
    else if (level == "2") return 7;
    else if (level == "3") return 10;
}

int pointDec(string level){
    if (level == "1") return 2;
    else if (level == "2") return 3;
    else if (level == "3") return 4;
}

double percent(int glueUsed){
    return (double) 1-(0.1*glueUsed);
}
