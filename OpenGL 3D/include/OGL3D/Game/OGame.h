#pragma once
#include <memory>

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
};

