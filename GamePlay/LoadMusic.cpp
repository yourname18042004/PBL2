#include "LoadMusic.h"
LoadMusic::LoadMusic() {
	SDL_Init(SDL_INIT_AUDIO);

	int audiorate = 48000;
	Uint16  audio_format = AUDIO_S32SYS;
	int audio_channels = 1;
	int audio_buffer = 2048;
	Mix_OpenAudio(audiorate, audio_format, audio_channels, audio_buffer);
}
LoadMusic::~LoadMusic() {
	SDL_Quit();
}
void LoadMusic::addSound(const char* SoundPath) {
	sound = Mix_LoadWAV(SoundPath);
}
void LoadMusic::playSound(const char* SoundPath) {
	Mix_PlayChannelTimed(-1, sound, 0,-1);

}