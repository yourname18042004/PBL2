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
	
	// chieu dai chieu rong button
	float width; 
	float height;

	// toa do ket thuc cua ruoi
	float end_x;
	float end_y;
	// thoi gian ruoi bat dau chay
	float *time_start;
	// thoi gian ruoi dung
	float *time_end;
	// toc do cua ruoi
	float speed;

	// toa do bat dau
	Vector start;
	// tao do ket thuc
	Vector end;

	// thu tu cua ruoi trong vector
	int num;

	// gioi han cua button tren man hinh
	SDL_FRect Area;
	SDL_Renderer* renderer;

	// in ra thu tu, thoi gian bat dau, thoi gian ket thuc cua button
	Content Num;
	Content TimeStart;
	Content TimeEnd;

	Buttons* Button = nullptr;
	// dung de xoa nut
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
	
	// cap nhat nhan su kien, cap toa do cua button
	void update(HandelEvent* Event, float delta);

	// renderer button
	void render(float above, float below);

	// gan lai toa do cho button
	void setNum(int num);
	//nhan su kien click 
	bool getClick(); 
	// nhan su kien xoa nut;
	bool getClickDelete();
};


#endif // 