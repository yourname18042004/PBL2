#include "FramesObject.h"


FramesObject::FramesObject(SDL_FRect* dest, const char* path, SDL_Renderer* renderer, bool loop) {
	Texture = LoadImage::Load(path, renderer);
	char tmp[100];
	for (int i = 0; i < strlen(path); i++) {
		tmp[i] = path[i];
	}
	char* tmpoftmp = strtok(tmp, "_");
	char* WidthImage = strtok(NULL, "_");
	char* HeightImage = strtok(NULL, "_");
	char* WidthAnimation = strtok(NULL, "_");
	char* HeightAnimation = strtok(NULL, ".");
	WidthImg = atoi(WidthImage);
	HeightImg = atoi(HeightImage);
	WidthAni = atoi(WidthAnimation);
	HeightAni = atoi(HeightAnimation);
	scr.x = 0;
	scr.y = 0;
	scr.w = WidthImg;
	scr.h = HeightImg;
	rectTmp = *dest;
	this->dest = dest;
	animation = new Animation(WidthAni/WidthImg, loop, 100);
	this->renderer = renderer;
	Index = 0;
}
void FramesObject::UpdateFrames() {
	animation->AnimationManager(Index);
	scr.x = Index * scr.w;
}
void FramesObject::Get_Texture() {
	SDL_RenderCopyF(renderer, Texture, &scr, dest);
}
void FramesObject::Get_Texture(double angle) {
	SDL_Rect tmp;
	tmp.x = (int)dest->x;
	tmp.y = (int)dest->y;
	tmp.w = (int)dest->w;
	tmp.h = (int)dest->h;
	SDL_RenderCopyEx(renderer, Texture, &scr, &tmp, angle, NULL, SDL_FLIP_NONE);
}
void FramesObject::Get_Texture(double angle, SDL_Point point) {
	SDL_Rect tmp;
	tmp.x = (int)dest->x;
	tmp.y = (int)dest->y;
	tmp.w = (int)dest->w;
	tmp.h = (int)dest->h;
	SDL_RenderCopyEx(renderer, Texture, &scr, &tmp, angle, &point, SDL_FLIP_NONE);
}
void FramesObject::ButtonAnimation() {
	if (CollisionButton(*dest))
	{
		dest->w = rectTmp.w * 1.2f;
		dest->h = rectTmp.h * 1.2f;
		dest->x = rectTmp.x - rectTmp.w * 0.2f / 2;
		dest->y = rectTmp.y - rectTmp.h * 0.2f / 2;
	}
	else {
		dest->w = rectTmp.w;
		dest->h = rectTmp.h;
		dest->x = rectTmp.x;
		dest->y = rectTmp.y;
	}
	animation->AnimationButton(Index, dest);
	scr.x = Index * scr.w;
	
}

void FramesObject::updateTmpRect(float x, float y)
{
	//rectTmp.x = x;
	rectTmp.y = y;
}