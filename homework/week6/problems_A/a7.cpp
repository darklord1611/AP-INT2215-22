#include <iostream>
using namespace std;

void swap(char* a, char* b) 
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void permute(string s, int left, int right) 
{
    if (left == right) 
        cout << s << endl;
    else 
    {
        for (int i = left; i <= right; i++) 
        {
            swap(&s[left], &s[i]);
            permute(s, left + 1, right);
            swap(&s[left], &s[i]); 
        }
    }
}

int main() {
    string s;
    cin >> s;
    permute(s, 0, s.size() - 1);
    return 0;
}
