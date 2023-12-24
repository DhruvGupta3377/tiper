#include <iostream>
#include <thread>
#include <chrono>
#include <bits/stdc++.h> 
#include <atomic>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <cstdlib>
using namespace std;


std::atomic<bool> stopTimer(false);
auto startTime = std::chrono::system_clock::now();
long timetaken;

void timecalculate() {
  while (!stopTimer) {
    auto currentTime = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    timetaken = elapsed;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
}

string inputString(){
	string input;
	getline(cin, input);
	return input;
}


std::string getRandomWords(const std::vector<std::string>& words, int count) {
    std::string result;
    std::srand(std::time(0)); // Seed for random number generation

    // Shuffle the vector of words
    std::vector<std::string> shuffledWords = words;
    std::random_shuffle(shuffledWords.begin(), shuffledWords.end());

    // Take the first 'count' words and concatenate them into a single string
    for (int i = 0; i < count && i < shuffledWords.size(); ++i) {
        result += shuffledWords[i];
        if (i < count - 1) {
            result += " "; // Add space between words, except for the last one
        }
    }

    return result;
}

string makestring(){
    std::ifstream inputFile("words.txt");
    std::vector<std::string> words;
    std::string word;
    while (std::getline(inputFile, word)) {
        words.push_back(word);
    }
    inputFile.close();
    std::string randomWordsString = getRandomWords(words, 10);
    // std::cout<< randomWordsString << std::endl;
    return randomWordsString;
}

void scoreGenerator(int errors,int promptCount, int inputCount){
	int score =  (promptCount - errors)*100/promptCount;
	int wpm = inputCount*60/timetaken;
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
	thread displayThread(timecalculate);
	string prompt = makestring();
	cout<<prompt<<endl<<endl;
	string input = inputString();
	checker(prompt, input);

  stopTimer = true;
  displayThread.join();
}