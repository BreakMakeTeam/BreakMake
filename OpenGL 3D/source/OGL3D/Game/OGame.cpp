#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <Windows.h>

OGame::OGame()
{
	gEngine = std::make_unique<OGraphicsEngine>();
	display = std::make_unique<OWindow>();

	display->makeCurrContext();

	gEngine->setViewport(display->getInnerSize());
}

OGame::~OGame()
{
}

void OGame::onCreate()
{
	gEngine->clear(OVec4(1, 0, 0, 1));


	display->present(false);
}

void OGame::onUpdate()
{
}

void OGame::onQuit()
{
}

void OGame::run()
{
	onCreate();
	while (isRunning)
	{
		MSG msg = {};
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) {
				isRunning = false;
				continue;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		onUpdate();
	}

	onQuit();
}

void OGame::quit()
{
	isRunning = false;
}
