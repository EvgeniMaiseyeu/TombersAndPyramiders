#pragma once
#include <string>
#include <SDL_mixer.h>

class AudioManager
{
private:
	static AudioManager* s_instance;
	
	Mix_Chunk* m_hit;
	Mix_Chunk* m_shootArrow;
	Mix_Chunk* m_swordSwing;
	Mix_Chunk* m_valiantWind;

	AudioManager();
	~AudioManager();

public:
	static AudioManager* getInstance();
	static void release();

	//Starts playing music
	void playMusic(int loop = -1, float volumeFactor = 1.0f);
	void playHitSFX(int loop = -1, float volumeFactor = 1.0f);
	void playShootArrowSFX(int loop = -1, float volumeFactor = 1.0f);
	void playSwordSwingSFX(int loop = -1, float volumeFactor = 1.0f);
	//Pauses the current music
	void pauseMusic();
	//Resume playing the music
	void resumeMusic();
	//Stops playing the music
	void stopMusic();
	//Starts sound effect, plays til the end and stops
	//void PlaySoundEffect(std::string filename, int loop = 0, int channel = 0);
};
