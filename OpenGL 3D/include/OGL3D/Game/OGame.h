#pragma once
#include <memory>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Math/OVec4.h>

class OGraphicsEngine;
class OWindow;
class OGame
{
public:
	OGame();
	~OGame();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onQuit();

	void run();
	void quit();

protected:
	bool isRunning = true;
	std::unique_ptr<OGraphicsEngine> gEngine;
	std::unique_ptr<OWindow> display;

	OVec4 color;
	OVec4 colorChange;

	OVertexArrayPtr VAOPtr;
};

