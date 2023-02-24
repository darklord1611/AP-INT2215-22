#include <iostream>

using namespace std;

void sort(int* arr, int size) 
{
    for(int i = 0; i < size;i++) 
    {
        for(int j = i + 1; j < size;j++) 
        {
            if(arr[j] < arr[i]) 
            {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}


int main()
{
    int n;
    cin >> n;
    int a[n], b[n + 1];
    for(int i = 0; i < n;i++) cin >> a[i];
    for(int i = 0; i <= n;i++) cin >> b[i];
    sort(a, n);
    sort(b, n + 1);
    int mysteryNumber = b[n];
    for(int i = 0; i < n;i++) 
    {
        if(a[i] - b[i] != 0) 
        {
            mysteryNumber = b[i];
            break;
        }
    }
    cout << mysteryNumber;
    return 0;
}
