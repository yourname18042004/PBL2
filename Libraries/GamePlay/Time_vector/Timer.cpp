#include "Timer.h"

Timer* Timer::sInit = NULL;
	

Timer* Timer::Init() {
	if (sInit == NULL)
		sInit = new Timer();
	return sInit;

}

void Timer::release() {
	delete sInit;
	sInit = NULL;

}
Timer::Timer() {
	reset();
	timeScale = 1.0f;
}

Timer::~Timer() {

}
void Timer::reset() {
	startTick = SDL_GetTicks();
	elapsedTick = 0;
	deltaTime = 0.0f;

}
float Timer::DeltaTime() {
	return deltaTime;

}
void Timer::TimeScale(float t) {
	timeScale = t;
}
float Timer::TimeScale() {
	return timeScale;
}
void Timer::Update() {

	elapsedTick = SDL_GetTicks() - startTick;
	deltaTime = (float)elapsedTick * 0.001f; 
	startTick = SDL_GetTicks();
}
	