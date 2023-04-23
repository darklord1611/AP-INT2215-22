#include "Utility.h"

int getHighScore(string path) 
{
    ifstream file(path.c_str());
    int value;
    if(file) 
    {
        file >> value;
        file.close();
    } else 
    {
        cout << "cant open file" << endl;
        return -1;
    }
    return value;
}

void replaceHighScore(int score, string path) 
{
    int highScore;
    ifstream file(path.c_str());
    if(file) 
    {
        file >> highScore;
        file.close();
    } else 
    {
        cout << "cant open file" << endl;
        return;
    }
    if(score > highScore) 
    {
        ofstream file(path.c_str());
        if(file) 
        {
            file << score;
            file.close();
        } else 
        {
            cout << "cant open file" << endl;
            return;
        }
    }
}

string modify(int value) 
{
    string str_score = to_string(value);
    for(int i = 0; i < 5 - str_score.size();i++) 
    {
        str_score = "0" + str_score;
    }
    return str_score;
}

void saveStats(string path, int current_score, int lives) 
{
    ofstream file(path.c_str());
    if(file.is_open()) 
    {
        file << current_score << endl;
        file << lives;
        file.close();
    } else 
    {
        cout << "cant open file" << endl;
    }
}

vector<int> getStats(string path) 
{
    vector<int> stat;
    ifstream file(path.c_str());
    if(file) 
    {
        int score;
        int lives;
        file >> score;
        file >> lives;
        stat.push_back(score);
        stat.push_back(lives);
        file.close();
    } else 
    {
        cout << "cant open file" << endl;
    }
    return stat;
}