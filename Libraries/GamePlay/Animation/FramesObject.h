#ifndef FRAMES_H
#define FRAMES_H
#include <SDL.h>
#include <string.h>
#include <Load/LoadTexture.h>
#include <Animation/Animation.h>
#include<cstring>
#pragma warning(disable : 4996)
/// <summary>
/// 
/// </summary>
class FramesObject {
private:
	SDL_Texture* Texture;
	SDL_Renderer* renderer;
	SDL_Rect scr; //Khung hình cắt ảnh, độ to của đối tượng và vị trí trên cửa sổ
	SDL_FRect* dest;
	int WidthImg, HeightImg;
	int WidthAni, HeightAni;
	int Index;
	int WidthImage, HeightImage;
	Animation* animation;

public:
	FramesObject(SDL_FRect* dest, const char* path, SDL_Renderer* renderer, bool loop);
	void Get_Texture();
	void UpdateFrames();
	int getWidthAni() {
		return WidthAni;
	}
	int getHeightAni() {
		return HeightAni;
	}
	int getMax_frame() {
		return (int)(WidthAni / HeightAni);
	}
	void setPositionDest(int x, int y) {
		(*dest).x = x;
		(*dest).y = y;
	}

	void setRunanimation() {
		animation->SetRunAnimation();
	}
};




#endif
