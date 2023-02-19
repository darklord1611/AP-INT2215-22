#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

bool isSquareNumber(int n) 
{
    int k = sqrt(n);
    return (k*k == n);
} 

int main()
{
    int n;
    cin >> n;
    if(isSquareNumber(n)) cout << "yes";
    else cout << "no";
    return 0;
}
