#include "PeakAEnginePCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
	#if __has_include(<vld.h>)
		#include <vld.h>
	#endif
#endif

#include "PeakAEngine.h"
//#include "steam_api.h"


int main(int, char*[]) {

	/*if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game! (SteamAPI_Init() failed);" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Successfully initialized Steam." << std::endl;
	}*/

	PeakAEngine engine;
	engine.Run();

	//SteamAPI_Shutdown();
    return 0;
}