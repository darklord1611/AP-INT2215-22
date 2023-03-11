#include "MenuState.h"

const string MenuState::s_menuID = "MENU";

void MenuState::update() {}

void MenuState::render() {}

bool MenuState::onEnter() 
{
    cout << "entering MenuState" << endl;
    return true;
}

bool MenuState::onEnter() 
{
    cout << "exiting MenuState" << endl;
    return true;
}