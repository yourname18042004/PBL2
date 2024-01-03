#ifndef TEXBOX_H
#define TEXBOX_H

#include <Init/Window.h>

class TextBox
{
private:
	float pos_x;
	float pos_y;
	float width;
	float height;

	SDL_FRect tex_rect;

	FramesObject* frame_tex;

	SDL_Renderer* renderer;
	
	std::string content;
	Content frame_content;

	bool setPick;
	bool back_space;
public:
	TextBox(float pos_x, float pos_y, float width, float height, SDL_Renderer* renderer);

	void Update(HandelEvent& event);

	void Render();
};

#endif // !TEXBOX_H
