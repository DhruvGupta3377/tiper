#include <iostream>
#include <thread>
#include <chrono>
#include <bits/stdc++.h> 
#include <atomic>
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
  errors = errors + abs(wordCount - 4);
  scoreGenerator(errors, 4, wordCount);
}

int main(){
	cout<<"\033[2J"<<endl;
	cout<<"\033[H"<<endl;
	thread displayThread(timecalculate);
	string prompt = "this is a string";
	cout<<prompt<<endl;
	string input = inputString();
	checker(prompt, input);

  stopTimer = true;
  displayThread.join();
}