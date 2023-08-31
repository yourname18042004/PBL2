#include "Object.h"

Object::Object(float pos_x, float pos_y, float width, float height, SDL_Renderer* Render, const char* file_path) {
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	renderer = Render;
	Texture = LoadImage::Load(file_path, Render);
	this->file_path = file_path;
	dest.x = pos_x;
	dest.y = pos_y;
	dest.w = width;
	dest.h = height;
	// đọc và tách thông số từ địa chỉ ảnh
	char tmp[100];
	for (int i = 0; i < strlen(file_path); i++) {
		tmp[i] = file_path[i];
	}
	char* tmpoftmp = strtok(tmp, "_");
	char* Width = strtok(NULL, "_");
	char* Height = strtok(NULL, ".");
	WidthAni = atoi(Width);
	HeightAni = atoi(Height);
	scr.w = HeightAni;
	scr.h = HeightAni;

}
void Object:: Render(SDL_Renderer* render) {
	SDL_RenderCopyF(render, Texture, &scr, &dest);
}
void Object::Animation() {
	scr.x = (count % (WidthAni / HeightAni)) * HeightAni;
	count++;
}
void Object:: UpdateObject(Vector v) {
	dest.x += v.x;
	dest.y += v.y;
	pos_x += v.x;
	pos_y += v.y;
}
void Object::setPosition(Vector v) {
	pos_x = v.x;
	pos_y = v.y;
	dest.x = v.x;
	dest.y = v.y;
}
SDL_FRect Object:: GetRect() {
	return dest;
}