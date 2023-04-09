#pragma once

#ifndef __MenuButton__
#define __MenuButton__

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class MenuButton : public ShooterObject
{
private:
	enum button_state
	{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
	};

	int m_callbackID;
	void (*m_callback) ();
	bool m_bReleased;
public:
	MenuButton();
	virtual void load(unique_ptr<LoaderParams> const &pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	void setCallback(void(*callback)()) { m_callback = callback; } // take a pointer pointing to function as parameter
	int getCallbackID() { return m_callbackID; }
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new MenuButton();
	}
};

#endif // define __MenuButton__