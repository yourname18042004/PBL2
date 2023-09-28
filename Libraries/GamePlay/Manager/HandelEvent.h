#ifndef HANDEL_EVENT_H
#define HANDEL_EVENT_H

#include <SDL.h>

class HandelEvent
{
public:
	bool BUTTON_LEFT = false;
	bool set = true;
	bool crossUp = false;
	bool crossDown = false;
	int MOUSE_X = 0;
	int MOUSE_Y = 0;
	
	void Handel(SDL_Event event)
	{

		if (BUTTON_LEFT) BUTTON_LEFT = false;
		if (event.type == SDL_MOUSEBUTTONUP) set = true;
		else if (event.button.button == SDL_BUTTON_LEFT)
		{
			MOUSE_X = event.motion.x;
			MOUSE_Y = event.motion.y;
			if (set) {
				BUTTON_LEFT = true;
				set = false;
			}
		}
		if (event.wheel.y == 1)
		{
			crossUp = true;
			crossDown = false;
		}
		if (event.wheel.y == -1)
		{
			crossDown = true;
			crossUp = false;
		}
		if (event.wheel.y == 0) {
			crossUp = false;
			crossDown = false;
		}
 	}
};

#endif // !HANDEL_EVENT_H
