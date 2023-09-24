﻿#ifndef COLLISION_HANDLING_
#define COLLISION_HANDLING_
#include<SDL.h>
// xử lý va chạm
static bool Collision(SDL_FRect a, SDL_FRect b) {
	return a.x <b.x + b.w && a.x + a.w >b.x && a.y <b.y + b.h && a.y + a.h >b.y;
}

static bool CollisionBlockWidth(SDL_FRect a) {
	return a.y <= 0|| a.y + a.h >= 680;
}

static bool CollisionBlockHeight(SDL_FRect a) {
	return a.x <= 0 || a.x + a.w >= 1400;
}
static bool CollisionButton(SDL_FRect a) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	return (x >= a.x && x <= a.x + a.w) && (y >= a.y && y <= a.y + a.h);
}
#endif