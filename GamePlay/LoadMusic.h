#ifndef LOADMUSIC_H
#define LOADMUSIC_H
#include<SDL.h>
#include<SDL_mixer.h>

class LoadMusic {
private:
	Mix_Chunk* sound;
public:
	LoadMusic();
	~LoadMusic();

	void addSound(const char* SoundPath);
	void playSound(const char* SoundPath);

};



#endif // DEBUG
