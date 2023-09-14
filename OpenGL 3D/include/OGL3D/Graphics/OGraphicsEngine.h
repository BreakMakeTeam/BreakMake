#pragma once
#include <OGL3D/Math/OVec4.h>
#include <OGL3D/Math/ORect.h>

class OGraphicsEngine
{
public:
	OGraphicsEngine();
	~OGraphicsEngine();

public:
	void clear(const OVec4& color);
	void setViewport(const ORect& rect);
};

