#pragma once
#include <map>

#include "Logger.h"

class AudioClip;

class SoundSystem
{
public:
	SoundSystem();
	virtual ~SoundSystem() = default;

	SoundSystem(const SoundSystem& other) = delete;
	SoundSystem(SoundSystem&& other) noexcept = delete;
	SoundSystem& operator=(const SoundSystem& other) = delete;
	SoundSystem& operator=(SoundSystem&& other) noexcept = delete;

	virtual void Play(int clipId);
	virtual int AddClip(const std::string& clipFilePath, int loops = 0);

protected:

private: 
	class SoundSystemImpl;
	SoundSystemImpl* m_pSoundSystem;
};

class NULL_SoundSystem final : public SoundSystem
{
public:
	NULL_SoundSystem() = default;
	virtual ~NULL_SoundSystem() override = default;

	NULL_SoundSystem(const NULL_SoundSystem& other) = delete;
	NULL_SoundSystem(NULL_SoundSystem&& other) noexcept = delete;
	NULL_SoundSystem& operator=(const NULL_SoundSystem& other) = delete;
	NULL_SoundSystem& operator=(NULL_SoundSystem&& other) noexcept = delete;
	

	void Play(int) override {}
	int AddClip(const std::string& /*clipFilePath*/, int /*loops*/) override { return 0; }
private:
};

class Logged_SoundSystem final : public SoundSystem
{
public:
	Logged_SoundSystem() : m_pSoundSystem{ new SoundSystem() } {}
	virtual ~Logged_SoundSystem() override { delete m_pSoundSystem; }

	Logged_SoundSystem(const Logged_SoundSystem& other) = delete;
	Logged_SoundSystem(Logged_SoundSystem&& other) noexcept = delete;
	Logged_SoundSystem& operator=(const Logged_SoundSystem& other) = delete;
	Logged_SoundSystem& operator=(Logged_SoundSystem&& other) noexcept = delete;

	void Play(int clipId) override
	{
		Logger::LogInfo("Playing Sound: \tId:" + std::to_string(clipId));
		m_pSoundSystem->Play(clipId);
	}
	int AddClip(const std::string& clipFilePath, int loops = 1) override
	{
		Logger::LogInfo("[SoundSystem] Loading Clip...");
		return m_pSoundSystem->AddClip(clipFilePath, loops);
	}

private:
	SoundSystem* m_pSoundSystem{};
};


