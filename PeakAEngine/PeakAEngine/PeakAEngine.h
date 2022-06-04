#pragma once
struct SDL_Window;
class PeakAEngine
{
public:
	PeakAEngine(float windowWidth, float windowHeight, bool useSteam = false)
		: m_UseSteam{ useSteam }
	{
		m_WindowWidth = windowWidth;
		m_WindowHeight = windowHeight;
	}
	virtual ~PeakAEngine() = default;

	void Initialize();
	virtual void LoadGame();
	void Cleanup();
	void Run();
	void Quit() { m_IsRunning = false; }

	static float WindowWidth() { return m_WindowWidth; }
	static float WindowHeight() { return m_WindowHeight; }

protected:
	static float m_WindowWidth;
	static float m_WindowHeight;
	static const int MsPerFrame = 16; //16 for 60 fps, 32 for 30 fps
	static const int MaxUpdatesPerFrame = 60; // Maximum calls of fixedupdate in 1 frame
	inline static const float FixedUpdateInterval = 0.01f;
	SDL_Window* m_Window{};
	bool m_UseSteam{ false };

	bool m_IsRunning{ true };
};
