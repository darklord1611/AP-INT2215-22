#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    string s[11];
    s[0] = "a";
    s[1] = "b";
    for(int i = 2; i < 11; i++) 
    {
        s[i] = s[i - 1] + s[i - 2];
    }
    for(int i = 0; i < 11;i++) cout << s[i] << endl;
    return 0;
}
