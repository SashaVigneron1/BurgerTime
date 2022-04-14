#pragma once
struct SDL_Window;
class PeakAEngine
{
public:
	PeakAEngine(bool useSteam = false)
		: m_UseSteam{ useSteam }
	{
	}

	void Initialize();
	virtual void LoadGame() const;
	void Cleanup();
	void Run();

protected:
	static const int MsPerFrame = 16; //16 for 60 fps, 32 for 30 fps
	static const int MaxUpdatesPerFrame = 60; // Maximum calls of fixedupdate in 1 frame
	SDL_Window* m_Window{};

	bool m_UseSteam{ false };
};
