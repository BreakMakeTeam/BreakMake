#include <OGL3D/Window/OWindow.h>
#include <Windows.h>
#include <assert.h>
#include <glad/glad.h>
#include <glad/glad_wgl.h>


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		OWindow* window = (OWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return NULL;
}

OWindow::OWindow()
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"OGL3DWindow";
	wc.lpfnWndProc = &WndProc;

	auto classID = RegisterClassEx(&wc);
	assert(classID);

	RECT rc = { 0,0,1024,768 };
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	handle = CreateWindowEx(
		NULL,
		MAKEINTATOM(classID),
		L"OGL3D Main Window",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, NULL, NULL
	);

	assert(handle);

	SetWindowLongPtr((HWND)handle, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow((HWND)handle, SW_SHOW);
	UpdateWindow((HWND)handle);

	// create openGL render context

	auto hDC = GetDC((HWND)handle);

	int pixelFDA[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0
	};

	int pixelForm = 0;
	UINT numForm  = 0;

	wglChoosePixelFormatARB(hDC, pixelFDA, nullptr, 1, &pixelForm, &numForm);
	assert(numForm);

	PIXELFORMATDESCRIPTOR pixelFD = {};
	DescribePixelFormat(hDC, pixelForm, sizeof(PIXELFORMATDESCRIPTOR), &pixelFD);
	SetPixelFormat(hDC, pixelForm, &pixelFD);

	int wglCAttr[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	context = wglCreateContextAttribsARB(hDC, 0, wglCAttr);
	assert(context);

}

OWindow::~OWindow()
{
	wglDeleteContext((HGLRC)context);
	DestroyWindow((HWND)handle);
}

ORect OWindow::getInnerSize()
{
	RECT rect = {};
	GetClientRect(HWND(handle), &rect);
	return ORect(rect.right - rect.left, rect.bottom - rect.top);
}

void OWindow::makeCurrContext()
{
	wglMakeCurrent(GetDC((HWND)handle), (HGLRC)context);
}

void OWindow::present(bool vsync)
{
	wglSwapIntervalEXT(vsync);
	wglSwapLayerBuffers(GetDC((HWND)handle), WGL_SWAP_MAIN_PLANE);
}
