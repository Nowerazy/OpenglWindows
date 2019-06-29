#pragma once
#include <Windows.h>
#include <gl/gl.h>
class GlContext
{
protected:
	int _format;
	HWND _hwnd;
	HDC _hdc;//设备上下文
	HGLRC _hrc;//opengl上下文
public:
	GlContext() {
		_format = 0;
		_hwnd = 0;
		_hdc = 0;
		_hrc = 0;
	}

	~GlContext() {
		shutdown();
	}
	bool setup(HWND hw, HDC hdc) {
		_hwnd = hw;
		_hdc = hdc;
		unsigned PixelFormat;
		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			24,
			8,
			0,
			PFD_MAIN_PLANE,
			0,
			0,
			0,
			0
		};
		if (_format == 0)
		{
			PixelFormat = ChoosePixelFormat(_hdc, &pfd);
		}
		else {
			PixelFormat = _format;
		}
		if (!SetPixelFormat(_hdc, PixelFormat, &pfd))
		{
			return false;
		}
		_hrc = wglCreateContext(_hdc);
		if (!wglMakeCurrent(_hdc, _hrc))
		{
			return false;
		}
		return true;
	}
	void shutdown() {
		if (_hrc != NULL)
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(_hrc);
			_hrc = NULL;
		}
		if (_hdc != 0)
		{
			ReleaseDC(_hwnd, _hdc);
			_hdc = NULL;
		}

	}
	void swapBuffer() {
		SwapBuffers(_hdc);
	}

};

