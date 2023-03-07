#include <iostream>

using namespace std;

int binarySearch(int* arr, int n, int x) 
{
    int low = 0, high = n - 1;
    while(low < high) 
    {
        int mid = (low + high) / 2;
        if(*(arr + mid) == x) 
        {
            return mid + 1;
        } else if(*(arr + mid) < x) low = mid + 1;
        else high = mid - 1;
    }
    if(*(arr + low) == x) return low + 1;
    return 0;
}

int main()
{
    int n, x;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n;i++) cin >> arr[i];
    cin >> x;
    cout << binarySearch(arr, n, x);
    return 0;
}
