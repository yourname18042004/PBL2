#ifndef LOADMUSIC_H
#define LOADMUSIC_H
#include<SDL.h>
#include<SDL_mixer.h>

class LoadMusic {
private:
	Mix_Chunk* sound;
	int channel;
public:
	LoadMusic(int channel) {
		SDL_Init(SDL_INIT_AUDIO);
		Mix_AllocateChannels(3);
		int audiorate = 48000;
		Uint16  audio_format = AUDIO_S32SYS;
		channel = channel;
		int audio_buffer = 2048;
		Mix_OpenAudio(audiorate, audio_format, channel, audio_buffer);
	}
	~LoadMusic() {
		
	}

	void addSound(const char* SoundPath) {

		sound = Mix_LoadWAV(SoundPath);

	}
	void playSound() {
		Mix_PlayChannelTimed(-1, sound, 0, -1);
	}
	void stopMusic() {
		Mix_HaltChannel(channel);
	}
};


#endif // DEBUG
