#include <iostream>

using namespace std;

int countEven(int* arr, int n) 
{
    int cnt = 0;
    for(int i = 0; i < n;i++) 
    {
        if(*(arr + i) % 2 == 0) cnt++;
    }
    return cnt;
}

int main()
{
    int n, x;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n;i++) cin >> arr[i];
    cout << countEven(arr, n);
    return 0;
}
