#include <iostream>

using namespace std;

string s = " abcdefghijklmnopqrstuvwxyz";
int N,k;

int arr[27];

bool isSameNumber(int* arr) 
{
    bool seen[26];
    fill_n(seen, 26, false);
    for(int i = 1; i <= k;i++) 
    {
        if(seen[arr[i]] == false) 
        {
            seen[arr[i]] = true;
        } else return true;
    }
    return false;
}


void check() 
{
    if(!isSameNumber(arr)) 
    {
        for(int i = 1; i <= k;i++) 
        {
            cout << s[arr[i]];
        }
        cout << endl;
    }
}

void recursion(int n) 
{
    if(n > k) 
    {
        check();
    }
    else 
    {
        for(int i = 1; i <= N;i++) 
        {
            arr[n] = i;
            recursion(n + 1);
        }
    }
}

int main()
{
    cin >> N >> k;
    recursion(1);
    return 0;
}
