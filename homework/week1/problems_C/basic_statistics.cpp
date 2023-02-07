#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n;i++) cin >> arr[i];
    int max = arr[0], min = arr[0], sum = arr[0];
    for(int i = 1; i < n;i++) {
        if(arr[i] > max) max = arr[i];
        if(arr[i] < min) min = arr[i];
        sum += arr[i]; 
    }
    double mean = (double) sum / n;
    cout << "mean: " << mean << endl;
    cout << "max: " << max << endl;
    cout << "min: " << min << endl;
    return 0;
}
