#pragma once
#include <memory>

class OVertexArrayObject;

typedef std::shared_ptr<OVertexArrayObject>	OVertexArrayPtr;

typedef float			f32;
typedef int				i32;
typedef unsigned int	ui32;

struct OVBufferData
{
	void* vertList = nullptr;
	ui32 vertSize = 0;
	ui32 listSize = 0;
};