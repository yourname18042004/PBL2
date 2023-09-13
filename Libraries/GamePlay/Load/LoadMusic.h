#ifndef LOADMUSIC_H
#define LOADMUSIC_H
#include<SDL.h>
#include<SDL_mixer.h>

class LoadMusic {
private:
	Mix_Chunk* sound;
public:
	void addSound(const char* SoundPath) {
		

		SDL_Init(SDL_INIT_AUDIO);
		int audiorate = 48000;
		Uint16  audio_format = AUDIO_S32SYS;
		int audio_channels = 1;
		int audio_buffer = 2048;
		Mix_OpenAudio(audiorate, audio_format, audio_channels, audio_buffer);

		sound = Mix_LoadWAV(SoundPath);
		
		Mix_PlayChannelTimed(-1, sound, 0, -1);
		//Mix_FreeChunk(sound);
		
		//sound = nullptr;
		//Mix_Quit();
	}
};



#endif // DEBUG
