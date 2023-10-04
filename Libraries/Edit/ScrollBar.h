#ifndef SCROLL_BAR_H
#define SCROLL_BAR_H

#include <Init/Window.h>

//THANH CUON THEO CHIEU NGANG
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

	bool MoveCroll(bool click); // DI CHUYEN THANH CUON 

	// LAY GIA TRI NHO NHAT VA GIA TRI LON NHAT MA THANH CUON TRA VE
	void setValue(float min, float max); 

	// lAY GIA TRI HIEN TAI MA THANH CUON TRA VE
	float getValue();
	float getData();

	// THANH DOI THANH CUON DUA VAO GIA TRI TRUYEN VAO
	void setValue(float value);

};

// THANH CUON THEO CHIEU DOC
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

	void MoveCroll(bool click);// DI CHUYEN THANH CUON 
	void MoveCrollWheel(HandelEvent* Event);

	// LAY GIA TRI NHO NHAT VA GIA TRI LON NHAT MA THANH CUON TRA VE
	void setValue(float min, float max);

	// lAY GIA TRI HIEN TAI MA THANH CUON TRA VE
	float getValue();
	void setValue(float value);
	
	// THANH DOI THANH CUON DUA VAO GIA TRI TRUYEN VAO
	float getData() { return value; }
};

#endif // !SCROLL_BAR_H
