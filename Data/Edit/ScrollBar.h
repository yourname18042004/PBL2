#ifndef SCROLL_BAR_H
#define SCROLL_BAR_H

#include <Init/Window.h>

class ScrollHorizontal
{
private:

	float pos_x;
	float pos_y;
	float width;
	float height;

	float value;
	float valueMin;
	float valueMax;

	SDL_FRect Scroll_Bar_Shaft;
	SDL_FRect Scroll_Bar_Part;
	SDL_FRect Scroll_Thumb;

	FramesObject* Frame_Scroll_Bar_Shaft;
	FramesObject* Frame_Scroll_Bar_Part;
	FramesObject* Frame_Scroll_Thumb;

	SDL_Renderer* renderer;

	bool follow = false;

public:
	ScrollHorizontal(float pos_x, float pos_y, float width, float height, SDL_Renderer* renderer);

	~ScrollHorizontal();


	void Render();

	bool MoveCroll(bool click);

	void setValue(float min, float max);

	float getValue();

	float getData();

	void setValue(float value);

};

class ScrollVertical
{
private:

	float pos_x;
	float pos_y;
	float width;
	float height;

	float value;
	float valueMin;
	float valueMax;

	SDL_FRect Scroll_Bar_Shaft;
	SDL_FRect Scroll_Bar_Part;
	SDL_FRect Scroll_Thumb;

	FramesObject* Frame_Scroll_Bar_Shaft;
	FramesObject* Frame_Scroll_Bar_Part;
	FramesObject* Frame_Scroll_Thumb;

	SDL_Renderer* renderer;

	bool follow;

public:
	ScrollVertical(float pos_x, float pos_y, float width, float height, SDL_Renderer* renderer);

	~ScrollVertical();


	void Render();

	void MoveCroll(bool click);
	void MoveCrollWheel(HandelEvent* Event);

	void setValue(float min, float max);

	float getValue();

	void setValue(float value);

	float getData() { return value; }
};

#endif // !SCROLL_BAR_H
