#include "FramesObject.h"



FramesObject::FramesObject(SDL_FRect* dest, const char* path, SDL_Renderer* renderer, bool loop) {
	Texture = LoadImage::Load(path, renderer);
	char tmp[100];
	for (int i = 0; i < strlen(path); i++) {
		tmp[i] = path[i];
	}
	char* tmpoftmp = strtok(tmp, "_");
	char* Width = strtok(NULL, "_");
	char* Height = strtok(NULL, ".");
	WidthAni = atoi(Width);
	HeightAni = atoi(Height);
	scr.x = 0;
	scr.y = 0;
	scr.w = HeightAni;
	scr.h = HeightAni;
	this->dest = dest;
	animation = new Animation(WidthAni/HeightAni, loop, 100);
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