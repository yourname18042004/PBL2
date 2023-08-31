#ifndef COLLISION_HANDLING_
#define COLLISION_HANDLING_
#include<SDL.h>
// xử lý va chạm
static bool Collision(SDL_FRect a, SDL_FRect b) {
	return a.x <b.x + b.w && a.x + a.w >b.x && a.y <b.y + b.h && a.y + a.h >b.y;
}

#endif