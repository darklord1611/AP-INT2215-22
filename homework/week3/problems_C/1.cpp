#include <iostream>

using namespace std;

int main()
{
    int n,a, k = 0;
    cin >> n;
    int arr[n];
    bool seen[n];
    fill_n(seen, n, false);
    for(int i = 0; i < n;i++) 
    {
        cin >> a;
        if(seen[a] == false) 
        {
            arr[k++] = a;
            seen[a] = true;
        }
    }
    if(k < n) cout << "yes";
    else cout << "no";
    return 0;
}
