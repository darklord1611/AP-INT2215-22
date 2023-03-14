#include <iostream>
#include <bits/stdc++.h>


using namespace std;


string getSubString(int pos, int len, string word) 
{
    string res = "";
    int cnt = 0;
    while(cnt < len) 
    {
        res += word[pos + cnt];
        cnt++;
    }
    return res;
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    char* str1 = &s1[0];
    int n1 = s1.size(), n2 = s2.size(), cnt = 0;
    for(int i = 0; i < n2; i++) 
    {
        if(i + n1 - 1 < n2)
        {
            string t = getSubString(i, n1, s2);
            if(strcmp(str1, &t[0]) == 0) cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}
