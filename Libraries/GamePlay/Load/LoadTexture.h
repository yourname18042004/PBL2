#ifndef LOAD_IMAGE_H
#define LOAD_IMAGE_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class LoadImage
{
public:
	// ham load anh cho doi tuong co bien "static"
	// nen co the goi ham o bat cu dau ma khong can phai 
	// tao doi tuong mien la da #include "LoadImage"
	static SDL_Texture* Load(const char* file, SDL_Renderer* render)
	{
		SDL_Texture* texture;
		SDL_Surface* image = IMG_Load(file);
		if (image)
		{
			texture = SDL_CreateTextureFromSurface(render, image);
			SDL_FreeSurface(image);
			return texture;
		}
		else std::cout << "Khong tim thay duong dan " << file << std::endl;
		return nullptr;
	}
};

#endif // !LOAD_IMAGE_H
