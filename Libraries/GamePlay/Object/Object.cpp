#include "Object.h"

Object::Object(float pos_x, float pos_y, float width, float height, SDL_Renderer* Render) {
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->width = width;
	this->height = height;
	renderer = Render;
}
