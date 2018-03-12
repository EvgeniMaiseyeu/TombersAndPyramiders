#include "AudioManager.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "SpriteRendererManager.h"
#include "HelperFunctions.h"

AudioManager* AudioManager::s_instance;

AudioManager* AudioManager::getInstance()
{
	if (s_instance == NULL)
		s_instance = new AudioManager();
	return s_instance;
}

void AudioManager::release()
{
	delete s_instance;
	s_instance = NULL;
}

AudioManager::AudioManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	m_hit = Mix_LoadWAV(BuildPath("Game/Assets/Audio/hit.mp3").c_str());
	m_shootArrow = Mix_LoadWAV(BuildPath("Game/Assets/Audio/shootarrow.mp3").c_str());
	m_swordSwing = Mix_LoadWAV(BuildPath("Game/Assets/Audio/swordswing.mp3").c_str());
	m_valiantWind = Mix_LoadWAV(BuildPath("Game/Assets/Audio/valiantwind.mp3").c_str());
}

AudioManager::~AudioManager()
{
	Mix_Quit();
}


void AudioManager::playMusic(int loop, float volumeFactor)
{
	Mix_PlayChannel(1, m_valiantWind, 0);
	Mix_Volume(1, 128 * volumeFactor);
}

void AudioManager::playHitSFX(int loop, float volumeFactor)
{
	Mix_PlayChannel(2, m_hit, 0);
	Mix_Volume(2, 128 * volumeFactor);
}

void AudioManager::playShootArrowSFX(int loop, float volumeFactor)
{
	Mix_PlayChannel(3, m_shootArrow, 0);
	Mix_Volume(3, 128 * volumeFactor);
}

void AudioManager::playSwordSwingSFX(int loop, float volumeFactor)
{
	Mix_PlayChannel(4, m_swordSwing, 0);
	Mix_Volume(4, 128 * volumeFactor);
}

/*void AudioManager::playMusic(std::string filename, int loops, float volumeFactor)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	Mix_Chunk *bgm = Mix_LoadWAV(filename.c_str());
	Mix_PlayChannel(1, bgm, 0);
	Mix_Volume(1, 10 * volumeFactor);
}
void AudioManager::playSEFshoot(std::string filename, int loops, float volumeFactor)
{
	//Mix_PlayMusic(mGameObj->GetMusic(filename), loops);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	Mix_Chunk *SEF = Mix_LoadWAV(filename.c_str());
	Mix_PlayChannel(2, SEF, 0);
	Mix_Volume(2, 128 * volumeFactor);
}*/

void AudioManager::pauseMusic()
{
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void AudioManager::resumeMusic()
{
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void AudioManager::stopMusic()
{
	Mix_CloseAudio();
}
