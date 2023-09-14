#pragma once
#include <OGL3D/Math/OVec4.h>
#include <OGL3D/Math/ORect.h>
#include <OGL3D/OPreq.h>

class OGraphicsEngine
{
public:
	OGraphicsEngine();
	~OGraphicsEngine();

	OVertexArrayPtr createVAO(const OVBufferData& data);

	void clear(const OVec4& color);
	void setViewport(const ORect& rect);
	void setVAO(const OVertexArrayPtr& vao);
	void drawTri(ui32 VCount, ui32 offset);
};

