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