#ifndef FRAME_H
#define FRAME_H

#include <Init/Window.h>
#include <TexBox.h>

class Frame
{
private:
	int pos_x;
	int pos_y;
	int width;
	int height;

	Buttons* OK;
	Buttons* Cancel;

	
	FramesObject* Area;
	SDL_Renderer* renderer;
public:
	Frame(int pos_x, int pos_y, int width, int height, SDL_Renderer* renderer);
	~Frame();
	void Update(HandelEvent& event);
	void Render();
};

#endif // !BOX_H
