#include "PeakAEnginePCH.h"
#include "ImGUIManager.h"

#include "imgui.h"
#include "Renderer.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

void ImGUIManager::Initialize(SDL_Window* pSDLWindow)
{
	m_pWindow = pSDLWindow;
	// ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_pWindow, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

ImGUIManager::~ImGUIManager()
{
	// ImGui
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void ImGUIManager::InitializeFrame()
{
	// ImGui Initialize Frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();
}