#ifndef _RACKET_
#define _RACKET_

#include "Object.h"
#include "HandelEvent.h"

class Racket : public Object {

private:
	

public:
	void update() {
		int x, y;
		SDL_GetMouseState(&x, &y);
		dest.x = (float)x;
		dest.y = (float)y;

	}
	void AnimationRacket(HandelEvent handel) {
		SDL_ShowCursor(false);
		if (handel.BUTTON_LEFT) {
			animation();
		}
			
		else if (!handel.BUTTON_LEFT) {
			count = 0;
			scr.x = 0;
		}
			
	}

};

#endif