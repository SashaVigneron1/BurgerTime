#include "PeakAEnginePCH.h"
#include "PeakAEngine.h"
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"

#include "ImGUIManager.h"

#include "steam_api.h"

float PeakAEngine::m_WindowHeight{ 480 };
float PeakAEngine::m_WindowWidth{ 640 };

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void PeakAEngine::Initialize()
{
	Logger::Initialize();

	srand((unsigned int)time(nullptr));

	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		(int)m_WindowWidth,
		(int)m_WindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	RENDERER.Init(m_Window);
	ImGUIManager::GetInstance().Initialize(m_Window);

	if (m_UseSteam)
	{
		Logger::EmptyLine();
		Logger::LogMessage("[PeakAEngine] Initializing Steam...", Logger::ConsoleColor::LightBlue);
		Logger::SetConsoleColor(Logger::ConsoleColor::LightBlue);

		if (!SteamAPI_Init())
		{
			Logger::LogError("[PeakAEngine] Fatal Error - Steam must be running to play this game!(SteamAPI_Init() failed)");
		}
		else
		{
			Logger::LogSuccess("[PeakAEngine] Successfully initialized Steam.");
		}

		Logger::EmptyLine();
	}
}

/**
 * Code constructing the scene world starts here
 */
void PeakAEngine::LoadGame()
{
}

void PeakAEngine::Cleanup()
{
	Logger::EmptyLine();
	Logger::LogInfo("[PeakAEngine] Cleaning up...");

	if (m_UseSteam) SteamAPI_Shutdown();

	RENDERER.Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void PeakAEngine::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("Resources/");

	LoadGame();
	{

		const auto& renderer = RENDERER;
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& imguiManager = ImGUIManager::GetInstance();
		auto timer = Time();
		//auto timer2 = Time(); This is not possible, since Time inherits from SingleInstance

		const float fixedUpdateInterval = FixedUpdateInterval;
		timer.SetFixedTime(fixedUpdateInterval);
		float fixedUpdateTimer = 0.0f;
		while (m_IsRunning)
		{
			sceneManager.RemoveMarkedObjects();

			int currFrame = 0;

			// currTime
			const auto startTime = std::chrono::high_resolution_clock::now();

			timer.CalculateTime();
			fixedUpdateTimer += Time::DeltaTime();

			imguiManager.InitializeFrame();
			m_IsRunning = input.ProcessInput();
			input.HandleInput();
			sceneManager.Update();
			sceneManager.OnGUI();
			if (m_UseSteam) SteamAPI_RunCallbacks();

			while (fixedUpdateTimer >= fixedUpdateInterval && currFrame <= MaxUpdatesPerFrame)
			{
				sceneManager.FixedUpdate();
				fixedUpdateTimer -= fixedUpdateInterval;
				currFrame++;
			}
			renderer.Render();

			const auto sleepTime = startTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now();
			std::this_thread::sleep_for(sleepTime); // In Short: Doesn't work properly because nr of milliseconds are rounded off to floor

			//// Somewhat closer to actual time
			//// Get The Duration We Need To Sleep For
			//const auto sleepTime = startTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now();
			//// Get The Nr Of Milliseconds
			//auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(sleepTime);
			//int nrNanos = (int)nanoseconds.count();
			//float nrMillis = nrNanos / 1000000.0f;

			//// Sleep
			//std::this_thread::sleep_until(std::chrono::high_resolution_clock::now() + std::chrono::milliseconds((int)round(nrMillis)));
		}

		sceneManager.DestroyAllScenes();
	}

	Cleanup();
}
