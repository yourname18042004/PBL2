#ifndef BUTTON_TABLE_H
#define BUTTON_TABLE_H

#include <Init/Gameplay.h>
#include <ScrollBar.h>
#include <Content.h>
#include <vector>
#include <string>

class ButtonTable
{
private:
	
	float width;
	float height;

	float end_x;
	float end_y;
	float *time_start;
	float *time_end;
	float speed;

	Vector start;
	Vector end;

	int num;

	SDL_FRect Area;
	SDL_Renderer* renderer;

	Content Num;
	Content TimeStart;
	Content TimeEnd;

	Buttons* Button = nullptr;
	Buttons* Delete = nullptr;

	
	float timeStart;
	float timeEnd;

public:float pos_x;
	  float pos_y;
	ButtonTable
	(
		float pos_x, float pos_y, float width, float height,
		float *time_start, float *time_end,
		SDL_Renderer* renderer, int num
	);
	void update(HandelEvent* Event, float delta);

	void render(float above, float below);

	void setNum(int num);
	bool getClick();
	bool getClickDelete();
};


#endif // 