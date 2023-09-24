#ifndef _TIMER_H_
#define _TIMER_H_
#include <SDL.h>

#include <iostream>


class Timer {
private:

	unsigned int startTick;
	unsigned int elapsedTick;
	float deltaTime;
	float timeScale;

public:
	static Timer* sInit;
	static Timer* Init();
	static void release();

	void reset();
	float DeltaTime();//Khoảng cách giữa 2 frames

	void TimeScale(float t);
	float TimeScale();

	void Update();

private:
	Timer();
	~Timer();

};

#endif // !_TIMER_H_
