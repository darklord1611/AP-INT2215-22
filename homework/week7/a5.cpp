#include <iostream>

using namespace std;

char* weirdString() 
{
    char c[] = "123456";
    return c;
}

int main()
{
    cout << weirdString();
    return 0;
}
