#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <glad/glad.h>
#include <glad/glad_wgl.h>
#include <assert.h>
#include <stdexcept>

OGraphicsEngine::OGraphicsEngine()
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"OGL3DDummyWindow";
	wc.lpfnWndProc = DefWindowProc;
	wc.style = CS_OWNDC;

	auto classID = RegisterClassEx(&wc);
	assert(classID);

	auto dHandle = CreateWindowEx(
		NULL,
		MAKEINTATOM(classID),
		L"",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, NULL, NULL
	);

	assert(dHandle);

	auto dummyDC = GetDC(dHandle);

	PIXELFORMATDESCRIPTOR pixelFD = {};
	pixelFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFD.nVersion = 1;
	pixelFD.iPixelType = PFD_TYPE_RGBA;
	pixelFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFD.cColorBits = 32;
	pixelFD.cAlphaBits = 8;
	pixelFD.cDepthBits = 24;
	pixelFD.cStencilBits = 8;
	pixelFD.iLayerType = PFD_MAIN_PLANE;

	auto pixelForm = ChoosePixelFormat(dummyDC,&pixelFD);
	SetPixelFormat(dummyDC, pixelForm, &pixelFD);


	auto dummyContext = wglCreateContext(dummyDC);
	assert(dummyContext);

	wglMakeCurrent(dummyDC, dummyContext);


	if (!gladLoadWGL(dummyDC)) {
		throw std::runtime_error("OGraphicsEngine - Error! - gladLoadWGL failed!");
	}

	if (!gladLoadGL()) {
		throw std::runtime_error("OGraphicsEngine - Error! - gladLoadGL failed!");
	}

	wglMakeCurrent(dummyDC, 0);
	wglDeleteContext(dummyContext);
	ReleaseDC(dHandle, dummyDC);
	DestroyWindow(dHandle);
}

OGraphicsEngine::~OGraphicsEngine()
{
}

OVertexArrayPtr OGraphicsEngine::createVAO(const OVBufferData& data)
{
	return std::make_shared<OVertexArrayObject>(data);
}

void OGraphicsEngine::clear(const OVec4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OGraphicsEngine::setViewport(const ORect& rect)
{
	glViewport(rect.left, rect.top, rect.width, rect.height);
}

void OGraphicsEngine::setVAO(const OVertexArrayPtr& vao)
{
	glBindVertexArray(vao->getID());
}

void OGraphicsEngine::drawTri(ui32 VCount, ui32 offset)
{
	glDrawArrays(GL_TRIANGLES, offset, VCount);
}
