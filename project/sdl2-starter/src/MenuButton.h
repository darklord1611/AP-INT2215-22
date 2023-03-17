#pragma once

#ifndef __MenuButton__
#define __MenuButton__

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "InputHandler.h"

class MenuButton : public SDLGameObject
{
private:
	enum button_state
	{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
	};

	void (*m_callback) ();

	bool m_bReleased;
public:
	MenuButton(const LoaderParams* pParams, void (*callback) ());
	virtual void draw();
	virtual void update();
	virtual void clean();
};

#endif // define __MenuButton__