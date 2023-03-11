
#ifndef __GameState__
#define __GameState__

#include<string>

using namespace std;

class GameState 
{
public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual bool onEnter() = 0; // similar to load function
    virtual bool onExit() = 0; // similar to clean function
    string getStateID() const = 0;

}



#endif // define __GameState__