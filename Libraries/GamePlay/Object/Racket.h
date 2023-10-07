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
		Racket1 = new FramesObject(&area, "Data//Picture//Racket_100_100_200_100.png", renderer, false);
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
		SDL_FRect tmp;
		tmp.x = area.x + area.w / 2;
		tmp.y = area.y + area.h / 2;
		tmp.h = area.h / 10;
		tmp.w = area.w / 10;
		return tmp;
	}
	void Updateifautorun(Vector EndFly) {
		area.x += FindDirection(EndFly).x * 12;
		area.y += FindDirection(EndFly).y * 12;
		if (area.x > 1440 || area.x < 0) area.x = 720;
		if (area.y > 720 || area.y < 0) area.y = 320;
		Racket1->setPositionDest(area.x, area.y);
	}
	Vector FindDirection(Vector EndFly) {
		Vector Find;
		Find.x  = EndFly.x - area.x;
		Find.y  = EndFly.y - area.y;
		float r = sqrt(Find.x * Find.x + Find.y * Find.y);
		Find.x = Find.x / r;
		Find.y = Find.y / r;
		return Find;
	}
	void AutoHit() {
		Racket1->setRunanimation();
		Racket1->UpdateFrames();
	}
};

#endif