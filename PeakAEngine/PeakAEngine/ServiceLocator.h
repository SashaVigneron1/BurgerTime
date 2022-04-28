#pragma once
#include "Singleton.h"
#include "SoundSystem.h"
class SoundSystem;

class ServiceLocator : public Singleton<ServiceLocator>
{
public:
	static SoundSystem* GetSoundSystem() { return m_pSoundSystem; }
	static void RegisterSoundSystem(SoundSystem* pSoundSystem) { m_pSoundSystem = pSoundSystem == nullptr ? &m_pDefaultSoundSystem : pSoundSystem; }

private:
	static SoundSystem* m_pSoundSystem;
	static NULL_SoundSystem m_pDefaultSoundSystem;

	//ToDo: Add Things Like Renderer ETC.
};
NULL_SoundSystem ServiceLocator::m_pDefaultSoundSystem;
SoundSystem* ServiceLocator::m_pSoundSystem = &m_pDefaultSoundSystem;

