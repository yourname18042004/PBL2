#ifndef _RACKET_
#define _RACKET_

#include "Object.h"
#include <Manager/HandelEvent.h>
#include <SDL.h>
class Racket : public Object {

private:
	SDL_FRect area;
	FramesObject* Racket1 = nullptr;
	HandelEvent* handleEvent;
public:
	Racket(float pos_x, float pos_y, float width, float height, SDL_Renderer* Render, HandelEvent *handleEvent) : Object(pos_x, pos_y, width, height, Render) 
	{
		area.x = pos_x;
		area.y = pos_y;
		area.w = width;
		area.h = height;
		this->handleEvent = handleEvent;
		Racket1 = new FramesObject(&area, "Data//Racket_100_100_200_100.png", renderer, false);
	}

	// update vị trí chuột
	void UpdatePositionOfMouse() {
		int x, y;
		SDL_GetMouseState(&x, &y);
		area.x = (float)(x - area.w / 2);
		area.y = (float)(y - area.h / 2);
		Racket1->setPositionDest(area.x, area.y);
	}
	void UpdateRacket()
	{
		if (GetHit()) {
		
			Racket1->setRunanimation();
		}
		Racket1->UpdateFrames();

	}

	bool GetHit() {
		return handleEvent->BUTTON_LEFT;
	}

	void Render()
	{
		Racket1->Get_Texture();
	}
	SDL_FRect GetArea() {
		return area;
	}
};

#endif