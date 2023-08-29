#ifndef HANDEL_EVENT_H
#define HANDEL_EVENT_H

#include <SDL.h>

class HandelEvent
{
public:
	bool BUTTON_LEFT = false;
	int MOUSE_X = 0;
	int MOUSE_Y = 0;
	bool Key[26] = {0};

	void Handel(SDL_Event event)
	{

		if (event.type == SDL_KEYDOWN)
		{
			for (int i = 0; i < 26; ++i)
			{
				int key = event.key.keysym.sym;
				Key[key - SDLK_a] = true;
			}
		}
		

		if (event.button.button == SDL_BUTTON_LEFT)
		{
			MOUSE_X = event.motion.x;
			MOUSE_Y = event.motion.y;
			BUTTON_LEFT = true;
		}

		if (event.type == SDL_MOUSEBUTTONUP)
		{
			BUTTON_LEFT = false;
		}
	}
};

#endif // !HANDEL_EVENT_H
