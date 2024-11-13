#include "Log.h"
#include <Res/ResourceManager.h>


int main()
{
	Breakout::Log::Init();

	Breakout::ResourceManager::InitShaders();
	Breakout::ResourceManager::InitTextures();
	BK_INFO("Hello, Logger!");
	return 0;
}

