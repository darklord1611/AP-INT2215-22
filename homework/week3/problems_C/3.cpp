#include <iostream>

using namespace std;

bool isPalindromeNumber(int num) 
{
    int copy = num;
    int reversedNum = 0;
    int digit;
    while(num != 0) 
    {
        digit = num % 10;
        reversedNum = reversedNum * 10 + digit;
        num /= 10;
    }
    if(copy == reversedNum) return true;
    return false;
}

int main()
{
    int T;
    cin >> T;
    while(T--) 
    {
        int a, b, cnt = 0;
        cin >> a >> b;
        for(int i = a;i <= b;i++) 
        {
            if(isPalindromeNumber(i)) cnt++;
        }
        cout << cnt << endl;
    }
    return 0;
}
