#include "PlayState.h"

string PlayState::s_playID = "PLAY";

void PlayState::update() {}

void PlayState::render() {}


bool PlayState::onEnter() 
{
    cout << "entering PlayState" << endl;
    return true;
}

bool PlayState::onExit() 
{
    cout << "exiting PlayState" << endl;
    return true;
}