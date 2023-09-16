#include "Animation.h"

Animation::Animation(int max_index_frame, bool loop, float times_to_change_frames) {
	this->max_index_frames = max_index_frame;
	this->loop = loop;
	if (this->loop) run = true;
	this->times_to_change_frames = times_to_change_frames;
	time = 0;

}
bool Animation::SetTime() {
	if (time >= times_to_change_frames) {
		time = 0;
		return true;
	}
	return false;
}

void Animation::AnimationManager(int& index) {
	time += Timer::sInit->DeltaTime();
	if (SetTime() && run) {
		index++;
	}
	if (index >= max_index_frames)
	{
		if (!loop) run = false;
		index = 0;
	}
		
}
