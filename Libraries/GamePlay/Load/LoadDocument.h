#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
class Font {
	// hàm trả về con trỏ texture font chữ cần ghi lên cửa sổ
public:
	static SDL_Texture* LoadCharac(const char* font, int size, SDL_Color Color, const char* content, SDL_Renderer* renderer)
	{
		// tạo con trỏ kiểu font gồm font và độ lớn của chữ
		TTF_Font* Font = TTF_OpenFont(font, size);
		if (!Font) std::cout << "dell tim dc font" << std::endl;
		SDL_Surface* surface = TTF_RenderText_Solid(Font, content, Color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		TTF_CloseFont(Font);
		return texture;

	}
};



#endif