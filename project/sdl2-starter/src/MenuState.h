#ifndef __MenuState__
#define __MenuState__

#include "GameState.h"
#include <vector>

using namespace std;

class MenuState: public GameState
{
protected:
	typedef void(*Callback) ();
	virtual void setCallbacks(const vector<Callback> &callbacks) = 0;
	vector<Callback> m_callbacks;
public:
	virtual void update() {};
    virtual void render() {};
    virtual bool onEnter() { return true; }; // similar to load function
    virtual bool onExit() { return true; }; // need to optimize
    virtual string getStateID() const { return " "; };
};


#endif // define __MenuState__