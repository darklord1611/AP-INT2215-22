#include <iostream>

using namespace std;

int gcd(int a, int b)
{
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main()
{
    int a,b;
    cin >> a >> b;
    int num = gcd(a,b);
    a /= num;
    b /= num;
    cout << a << "/" << b;
    return 0;
}
