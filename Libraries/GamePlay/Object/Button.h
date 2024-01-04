#ifndef BUTTOM_H
#define BUTTOM_H
#include <SDL.h>
#include<Vacham/CollisionHandling.h>
#include<Animation/FramesObject.h>
class Buttons{
private:
	SDL_FRect Dest;
	SDL_Rect Scr;
	float pos_x, pos_y, width, height;
	SDL_Renderer* renderer;
	bool click = false;
	FramesObject* frame = nullptr;
public:
	Buttons(float x, float y, float width, float height, const char* filepath, SDL_Renderer* renderer) {
		this->pos_x = x;
		this->pos_y = y;
		this->width = width;
		this->height = height;
		this->renderer = renderer;
		Dest.x = pos_x - width / 2;
		Dest.y = pos_y - height / 2;
		Dest.h = height;
		Dest.w = width;
		frame = new FramesObject(&Dest, filepath, renderer, false);
	}
	void Render() {
		frame->Get_Texture();
	}
	void Setclick(bool press) {
		frame->ButtonAnimation();
		if (CollisionButton(Dest) && press)
			click = true;
		else click = false;
	}
	bool Getclick() {
		return click;
	}
	void setDest(float x, float y)
	{
		Dest.x = x;
		Dest.y = y;
		frame->updateTmpRect(x, y);
	}

	SDL_FRect getDest() { return Dest; }
};

class TrueFalse : public Buttons {
private:
	FramesObject* frame2 = nullptr;
public:
	TrueFalse(float x, float y, float width, float height, const char* filepath, SDL_Renderer* renderer, const char* filepath2) :
		Buttons(x,  y,  width, height, filepath, renderer) {
		SDL_FRect a;
		a.x = x - width / 2;
		a.y = y - height / 2;
		a.h = height;
		a.w = width;
		frame2 = new FramesObject(&a, filepath2, renderer, false);
		
	}
	void RenderTrueFalse(bool set) {
			
			frame2->Get_Texture();
		
	}

};

#endif