#pragma once
#include <OGL3D/OPreq.h>

class OVertexArrayObject
{
public:
	OVertexArrayObject(const OVBufferData& data);
	~OVertexArrayObject();

	ui32 getID();
private:
	ui32 VBufferID = 0;
	ui32 VArrayID  = 0;
};

