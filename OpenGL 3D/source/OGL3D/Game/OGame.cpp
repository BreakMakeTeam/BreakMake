#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <Windows.h>
#include <iostream> //TEMP

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
	const f32 Verts[] = {
		-0.5f,-0.5f,0.0f,
		 0.5f,-0.5f,0.0f,
		 0   , 0.5f,0.0f
	};

	VAOPtr = gEngine->createVAO({ (void*)Verts, sizeof(f32) * 3, 3 });

	color		= OVec4(1, 0.5f, 0, 1);
	colorChange = OVec4(0.01f, 0.005f, 0.015f, 0);
}

void OGame::onUpdate()
{
	gEngine->clear(color);

	color.x += colorChange.x;
	color.y += colorChange.y;
	color.z += colorChange.z;
	if (color.x > 1.0f || color.x < 0) colorChange.x = -colorChange.x;
	if (color.y > 1.0f || color.y < 0) colorChange.y = -colorChange.y;
	if (color.z > 1.0f || color.z < 0) colorChange.z = -colorChange.z;
	//std::cout << "" << color.x << "\t" << color.y << "\t" << color.z << "\n\n";

	gEngine->setVAO(VAOPtr);

	gEngine->drawTri(3, 0);

	display->present(false);
	Sleep(25);
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
