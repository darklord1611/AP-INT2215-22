#include <iostream>

using namespace std;

string reverse(string s) 
{
    int n = s.size();
    for(int i = 0; i < n / 2;i++) 
    {
        char tmp = s[i];
        s[i] = s[n - 1 - i];
        s[n - 1 - i] = tmp;
    }
    return s;
}

int main()
{
    int n;
    cin >> n;
    string s[n], res = "";
    for(int i = 0; i < n;i++) cin >> s[i];
    for(int i = 0; i < n;i++) 
    {
        for(int j = i + 1; j < n;j++) 
        {
            if(s[i] == reverse(s[j])) 
            {
                res = s[i];
                break;
            }
        }
    }
    cout << res.size() << " " << res[res.size() / 2];
    return 0;
}
