#ifndef ANIMATION_H
#define ANIMATION_H
#include<Time_vector/Timer.h>
#include <iostream>
class Animation {
private:
	float time;
	int max_index_frames;
	bool loop;
	bool run;
	float times_to_change_frames;
public:
	Animation(int max_index_frame, bool loop, float times_to_change_frames);
	void AnimationManager(int& index);
	bool SetTime();
	void SetRunAnimation() { run = true; };
};








#endif //2 hon dai t
