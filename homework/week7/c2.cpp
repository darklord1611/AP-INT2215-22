#include <iostream>
#include <bits/stdc++.h>


using namespace std;

const int start_point = 0;
const int end_point = 70;


struct Rabbit 
{
    int current_pos;
    void move() 
    {
        int num = rand() % 100 + 1;
        if(1 <= num && num <= 30) current_pos += 1;
        else if(num <= 50) current_pos -= 2;
        else if(num <= 70) current_pos += 9;
        else if(num <= 80) current_pos -= 12;
        
        if(current_pos < 0) current_pos = 0;
    }
};

struct Turtle 
{
    int current_pos;
    void move() 
    {
        int num = rand() % 100 + 1;
        if(1 <= num && num <= 30) current_pos += 1;
        else if(num <= 50) current_pos -= 6;
        else current_pos += 3;
        
        if(current_pos < 0) current_pos = 0;
    }
};


void print(Turtle &t, Rabbit &r) 
{
    cout << "Rabbit: " << r.current_pos << " & Turtle: " << t.current_pos << endl;
}

int main()
{
    srand(time(NULL));
    Turtle turtle;
    turtle.current_pos = 0;
    Rabbit rabbit;
    rabbit.current_pos = 0;
    while(turtle.current_pos < 70 && rabbit.current_pos < 70) 
    {
        turtle.move();
        if(turtle.current_pos > 70) 
        {
            cout << "Turtle wins" << endl;
            break;
        }
        rabbit.move();
        if(rabbit.current_pos > 70) 
        {
            cout << "Rabbit wins" << endl;
            break;
        }
        print(turtle, rabbit);
    }
    return 0;
}
