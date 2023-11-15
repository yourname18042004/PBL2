#ifndef LOADMUSIC_H
#define LOADMUSIC_H
#include<SDL.h>
#include<SDL_mixer.h>

class LoadMusic {
private:
	Mix_Chunk* sound;
	int channel;
public:
	LoadMusic(int Channel) {
		SDL_Init(SDL_INIT_AUDIO);
		Mix_AllocateChannels(10);
		int audiorate = 48000;
		Uint16  audio_format = AUDIO_S32SYS;
		this->channel = Channel;
		int audio_buffer = 2048;
		Mix_OpenAudio(audiorate, audio_format, channel, audio_buffer);
	}
	~LoadMusic() {
		
	}

	void addSound(const char* SoundPath) {

		sound = Mix_LoadWAV(SoundPath);
	}
	void playSound(int loops) {

		Mix_PlayChannelTimed(channel, sound, loops, -1);

	}

	void stopMusic() {

		Mix_HaltChannel(channel);
	}

	void updateVolume(float volumeValue) {

		Mix_Volume(channel, volumeValue);
	}
};


#endif // DEBUG
