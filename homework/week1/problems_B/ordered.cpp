#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    bool d = false;
    int a,b,c;
    cin >> a >> b >> c;
    if((c - b > 0 && b - a > 0) || (a - b > 0 && b - c > 0)) {
        d = true;
    }
    cout << d;
    return 0;
}
