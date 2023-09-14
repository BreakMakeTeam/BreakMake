#pragma once
#include <OGL3D/Math/ORect.h>



class OWindow
{
public:
	OWindow();
	~OWindow();

	ORect getInnerSize();

	void makeCurrContext();
	void present(bool vsync);
private:
	void* handle  = nullptr;
	void* context = nullptr;
};

