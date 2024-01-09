#include <iostream>
#include <chrono>
#include <bits/stdc++.h> 
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
using namespace std;



auto startTime = std::chrono::high_resolution_clock::now();
double timetaken;

void timecalculate() {
    auto endTime = std::chrono::high_resolution_clock::now();
    timetaken = std::chrono::duration<double, std::milli>(endTime-startTime).count();
}

string inputString(){
	string input;
	getline(cin, input);
	return input;
}


string getRandomWords(const vector<string>& words, int count) {
    string result;
    srand(time(0));
    vector<string> shuffledWords = words;
    random_shuffle(shuffledWords.begin(), shuffledWords.end());
    for (int i = 0; i < count && i < shuffledWords.size(); ++i) {
        result += shuffledWords[i];
        if (i < count - 1) {
            result += " ";
        }
    }
    return result;
}

string makestring(){
    ifstream inputFile("words.txt");
    vector<std::string> words;
    string word;
    while (getline(inputFile, word)) {
        words.push_back(word);
    }
    inputFile.close();
    string randomWordsString = getRandomWords(words, 10);
    return randomWordsString;
}

void scoreGenerator(int errors,int promptCount, int inputCount){
    timecalculate();
	int score =  (promptCount - errors)*100/promptCount;
    int temp = (int) timetaken;
	int wpm = inputCount*60000/timetaken;
	cout<<"score                  : "<<score<<"%"<<endl;
	cout<<"wpm (words per minute) : "<<wpm<<endl;
}


void checker(string prompt, string input){
  istringstream promptStream(prompt);
  istringstream promptStream1(input);
  istringstream inputStream(input);

  string word, word1, word2;
  int errors{0};
  int wordCount = 0;

  while (promptStream1 >> word) {
      ++wordCount;
  }


  while (promptStream >> word1 && inputStream >> word2) {
      if (word1 != word2) {
  				errors += 1;
      }
  }
  errors = errors + abs(wordCount - 10);
  scoreGenerator(errors, 10, wordCount);
}

int main(){
	cout<<"\033[2J"<<endl;
	cout<<"\033[H"<<endl;
	string prompt = makestring();
	cout<<prompt<<endl<<endl;
	string input = inputString();
	checker(prompt, input);
}
