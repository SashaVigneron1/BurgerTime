#include "PeakAEnginePCH.h"
#include "PeakAEngine.h"
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"

#include "ImGUIManager.h"
#include "Logger.h"

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
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
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

	Renderer::GetInstance().Init(m_Window);
	ImGUIManager::GetInstance().Initialize(m_Window);

	if (m_UseSteam)
	{
		Logger::EmptyLine();
		Logger::LogMessage("Initializing Steam...", Logger::ConsoleColor::LightBlue);
		Logger::SetConsoleColor(Logger::ConsoleColor::LightBlue);

		if (!SteamAPI_Init())
		{
			Logger::LogError("Fatal Error - Steam must be running to play this game!(SteamAPI_Init() failed)");
		}
		else
		{
			Logger::LogSuccess("Successfully initialized Steam.");
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
	if (m_UseSteam) SteamAPI_Shutdown();

	Renderer::GetInstance().Destroy();
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
		const auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& imguiManager = ImGUIManager::GetInstance();
		auto timer = Time();
		//auto timer2 = Time(); This is not possible, since Time inherits from SingleInstance

		constexpr float fixedUpdateInterval = MsPerFrame / 100.f;
		timer.SetFixedTime(fixedUpdateInterval);
		float fixedUpdateTimer = 0.0f;
		bool isRunning = true;
		while (isRunning)
		{
			int currFrame = 0;

			// currTime
			const auto startTime = std::chrono::high_resolution_clock::now();

			timer.CalculateTime();
			fixedUpdateTimer += Time::DeltaTime();

			imguiManager.InitializeFrame();
			isRunning = input.ProcessInput();
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

	}

	Cleanup();
}
