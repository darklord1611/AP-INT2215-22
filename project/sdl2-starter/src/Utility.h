#ifndef __Utility__
#define __Utility__

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int getHighScore(string path);
string modify(int value);
void replaceHighScore(int score, string path);
void saveStats(string path, int score, int lives, int currentRound, int isRoundComplete);
vector<int> getStats(string path); 
#endif