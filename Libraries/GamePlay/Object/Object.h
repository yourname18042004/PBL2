#ifndef OBJECT_H_
#define OBJECT_H_
#pragma warning(disable : 4996)
#include<SDL.h>
#include<SDL_image.h>
#include<cstring>
#include<string.h>
#include <Load/LoadTexture.h>
#include <Time_vector/Vector.h>
#include <Time_vector/Timer.h>
#include<Animation/Animation.h>
#include<Animation/FramesObject.h>

class Object {
protected:
	float pos_x; // Vị trí ban đầu 
	float pos_y;
	int width, height;
	SDL_Renderer* renderer;

public:
	// Khởi tạo đối tượng
	Object(float pos_x, float pos_y, float width, float height, SDL_Renderer* Render);
};

#endif