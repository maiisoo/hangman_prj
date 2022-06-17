#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

pair<string,string> chooseWord(string level, string topic)
{
    vector<string> vocab, definition;
    string fileName;
    if (level == "1")
    {
            if (topic == "1")
                fileName = "./word_list/easy_plants.txt";
            else if (topic == "2")
                fileName = "./word_list/easy_animals.txt";
            else if (topic == "3")
                fileName = "./word_list/easy_others.txt";
        ifstream myfile(fileName.c_str());
        if (myfile.is_open())
        {
            string line, word;
            while (getline(myfile,line))            //Read a line - contains word & its definition
            {
                size_t pos = line.find(" ");        //Find the position of first occurrence of 'space'
                word = line.substr(0, pos);         //Get the word
                vocab.push_back(word);
                definition.push_back(line.erase(0,pos));         //The remaining of line is definition. Indexes of the word and its definition are the same.
            }
            myfile.close();
        }
        else
        {
            throw domain_error("Error: Failed to open this file. " + fileName);
        }
    }
    else if (level == "2")
    {
        if (topic == "1")
            fileName = "./word_list/medium_plants.txt";
        else if (topic == "2")
            fileName = "./word_list/medium_animals.txt";
        else if (topic == "3")
            fileName = "./word_list/medium_others.txt";
        ifstream myfile(fileName.c_str());
        if (myfile.is_open())
        {
            string line, word;
            while (getline(myfile, line))
            {
                size_t pos = line.find(" ");
                word = line.substr(0, pos);
                vocab.push_back(word);
                definition.push_back(line.erase(0,pos));
            }
            myfile.close();
        }
        else
        {
            throw domain_error("Error: Failed to open this file. " + fileName);
        }
    }
    else if (level == "3")
    {
        if (topic == "1")
            fileName = "./word_list/hard_plants.txt";
        else if (topic == "2")
            fileName = "./word_list/hard_animals.txt";
        else if (topic == "3")
            fileName = "./word_list/hard_others.txt";
        ifstream myfile(fileName.c_str());
        if (myfile.is_open())
        {
            string line,word;
            while (getline(myfile, line))
            {
                size_t pos = line.find(" ");
                word = line.substr(0, pos);
                vocab.push_back(word);
                definition.push_back(line.erase(0,pos));
            }
            myfile.close();
        }
        else
        {
            throw domain_error("Error: Failed to open this file. " + fileName);
        }
    }
    if (!vocab.empty()&&!definition.empty())
    {
        srand(time(NULL));
        int index = rand() % vocab.size();
        string chosenWord = vocab[index], chosenWord_def = definition[index];
        return make_pair(chosenWord,chosenWord_def);
    }
    else
        return make_pair("book","sách");
}
