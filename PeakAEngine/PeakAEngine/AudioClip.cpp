#include "PeakAEnginePCH.h"
#include "AudioClip.h"

#include "Logger.h"
#include "SDL_mixer.h"

AudioClip::AudioClip(const std::string& filepath)
	: m_FilePath{ filepath }
{
	m_pChunk = Mix_LoadWAV(m_FilePath.c_str());
	if (m_pChunk == nullptr)
	{
		Logger::LogError("[AudioClip] Something went wrong trying to load file: ", Mix_GetError());
	}
}

AudioClip::~AudioClip()
{
	if (m_pChunk)
		Mix_FreeChunk(m_pChunk);
}

void AudioClip::Play()
{
	if (m_pChunk)
		Mix_PlayChannel(-1, m_pChunk, 0);
}

void AudioClip::SetVolume(int volume)
{
	if (m_pChunk)
		Mix_VolumeChunk(m_pChunk, volume);
}

int AudioClip::GetVolume()
{
	// If less than 0 then chunk volume will not be set
	if (m_pChunk)
		return Mix_VolumeChunk(m_pChunk, -1);
	return 0;
}
