#ifndef FRAMES_H
#define FRAMES_H
#include <SDL.h>
#include <string.h>
#include <Load/LoadTexture.h>
#include <Animation/Animation.h>
#include<cstring>
#pragma warning(disable : 4996)

class FramesObject {
private:
	SDL_Texture* Texture;
	SDL_Renderer* renderer;
	SDL_Rect scr; //Khung hình cắt ảnh, độ to của đối tượng và vị trí trên cửa sổ
	SDL_FRect* dest;
	SDL_FRect rectTmp;
	int WidthImg, HeightImg;
	int WidthAni, HeightAni;
	int Index;
	int WidthImage, HeightImage;
	Animation* animation;

public:
	FramesObject(SDL_FRect* dest, const char* path, SDL_Renderer* renderer, bool loop);
	void Get_Texture();
	void Get_Texture(double angle); // xoay hinh tai vi tri trung tam cua hinh
	void Get_Texture(double angle, SDL_Point); // xoay hinh tai vi tri bay ki cua hinh
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
	void ButtonAnimation();

	void updateTmpRect(float x, float y);
};




#endif
