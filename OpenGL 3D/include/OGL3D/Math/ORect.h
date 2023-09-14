#pragma once
#include <OGL3D/OPreq.h>

class ORect
{
public:
	ORect() {}
	ORect(i32 w, i32 h) : width(w),height(h) {}
	ORect(i32 l, i32 t,i32 w, i32 h) : left(l), top(t), width(w), height(h) {}
	ORect(const ORect& ref) : left(ref.left), top(ref.top), width(ref.width), height(ref.height) {}

	i32 width = 0, height = 0, left = 0, top = 0;
};