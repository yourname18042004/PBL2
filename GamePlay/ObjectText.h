#ifndef TEXT_H
#define TEXT_H
#include<SDL.h>
#include "LoadDocument.h"
class Text {
protected:
	SDL_Texture* texture;
	SDL_FRect dest;
	SDL_Rect src;
	SDL_Renderer* renderer;
public:
	//Khởi tạo text;
	void init(int x, int y, int w, int h, 
		const char* font, int size, SDL_Color Color, 
		const char* content, SDL_Renderer* renderer) 
	{
		texture = Font::LoadCharac(font, size, Color, content, renderer);
		this->renderer = renderer;
		dest.w = w;
		dest.h = h;
		dest.x = x;
		dest.y = y;

	}
	//cập nhật lại text
	void update(int x, int y, int w, int h,
		const char* font, int size, SDL_Color Color,
		const char* content, SDL_Renderer* renderer) {
		texture = Font::LoadCharac(font, size, Color, content, renderer);
		dest.w = w;
		dest.h = h;
		dest.x = x;
		dest.y = y;
	}
	void render(SDL_Renderer* renderer) {
		SDL_RenderCopyF(renderer, texture, NULL, &dest);
	}
};

#endif