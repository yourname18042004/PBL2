#ifndef HANDEL_EVENT_H
#define HANDEL_EVENT_H

#include <SDL.h>

class HandelEvent
{
public:
	bool BUTTON_LEFT = false;
	int MOUSE_X = 0;
	int MOUSE_Y = 0;

	void Handel(SDL_Event event)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			MOUSE_X = event.motion.x;
			MOUSE_Y = event.motion.y;
			BUTTON_LEFT = true;
		}
		
	}
};

#endif // !HANDEL_EVENT_H
