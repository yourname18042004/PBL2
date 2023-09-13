#ifndef MENU_BACKGROUND_H
#define MENU_BACKGROUND_H
#include <Load/LoadTexture.h>
#include <SDL.h>


class LoadMenu {
protected:
	SDL_Texture* Texture;
	SDL_Renderer* renderer;
public:
	void LoadMandB(SDL_Renderer* renderer, const char* filepath) {
		this->renderer = renderer;
		Texture = LoadImage::Load(filepath, renderer);
	}
	void Render(SDL_Renderer* renderer) {
		SDL_RenderCopy(renderer, Texture, NULL, NULL);
	}


};




#endif