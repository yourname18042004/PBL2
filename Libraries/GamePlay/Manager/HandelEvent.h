
#ifndef HANDEL_EVENT_H
#define HANDEL_EVENT_H

#include <SDL.h>

class HandelEvent
{
public:
	bool BUTTON_LEFT = false;
	bool BUTTON_LEFT_PRESS = false; /////////////////////////////// chinh sua o day
	bool set = true;
	bool crossUp = false;
	bool crossDown = false;
	int MOUSE_X = 0;
	int MOUSE_Y = 0;

	const Uint8 *Key = SDL_GetKeyboardState(NULL);;

	SDL_Event event;

	void Handel(SDL_Event& event)
	{
		this->event = event;
		if (BUTTON_LEFT) BUTTON_LEFT = false;
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			BUTTON_LEFT_PRESS = false;/////////////////////////////// chinh sua o day
			set = true;
		}

		else if (event.button.button == SDL_BUTTON_LEFT)
		{
			MOUSE_X = event.motion.x;
			MOUSE_Y = event.motion.y;
			if (set) {
				BUTTON_LEFT = true;
				set = false;
			}
			BUTTON_LEFT_PRESS = true;/////////////////////////////// chinh sua o day
		}
		if (event.wheel.y == -1)
		{
			crossUp = true;
			crossDown = false;
		}
		if (event.wheel.y == 1)
		{
			crossDown = true;
			crossUp = false;
		}
		if (event.wheel.y == 0) {
			crossUp = false;
			crossDown = false;
		}
	}

	bool getBachSpace()
	{
		return Key[SDL_SCANCODE_BACKSPACE];
	}
};

#endif // !HANDEL_EVENT_H