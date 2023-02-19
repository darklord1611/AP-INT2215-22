#include <iostream>

using namespace std;

bool isPalindrome(string word) 
{
    string t = word;
    int n = word.size();
    for(int i = 0; i < n / 2;i++) 
    {
        char tmp = word[i];
        word[i] = word[n - 1 - i];
        word[n - 1 - i] = tmp;
    }
    if(t == word) return true;
    return false;
}


int main()
{
    string word;
    cin >> word;
    if(isPalindrome(word)) cout << "yes";
    else cout << "no";
    return 0;
}
