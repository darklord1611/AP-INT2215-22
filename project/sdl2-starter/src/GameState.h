
#ifndef __GameState__
#define __GameState__

#include <string>
#include <iostream>
using namespace std;

class GameState 
{
public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual bool onEnter() = 0; // similar to load function
    virtual bool onExit() = 0; // similar to clean function
    virtual string getStateID() const = 0;

    virtual ~GameState() = default;
};



#endif // define __GameState__